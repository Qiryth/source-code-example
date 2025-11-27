// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AbilityTasks/MoveUnitAbilityTask.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Gameplay/GameplayTagDeclarations.h"
#include "Karawan/Units/UnitBase.h"
#include "Navigation/PathFollowingComponent.h"

UMoveUnitAbilityTask* UMoveUnitAbilityTask::CreateMoveUnitProxy(UGameplayAbility* OwningAbility, const FName TaskInstanceName, AActor* TargetActor,
                                                                const FVector TargetLocation, bool CancelAbilityOnFailed)
{
	UMoveUnitAbilityTask* AbilityTask = NewAbilityTask<UMoveUnitAbilityTask>(OwningAbility, TaskInstanceName);

	AbilityTask->TargetActor = TargetActor;
	AbilityTask->TargetLocation = TargetLocation;
	AbilityTask->bCancelAbilityOnFailed = CancelAbilityOnFailed;
	
	return AbilityTask;
}

UMoveUnitAbilityTask::UMoveUnitAbilityTask()
{
	bTickingTask = false;
}

void UMoveUnitAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	if (OwningUnit.IsValid())
	{
		OwningUnit->GetAbilitySystemComponent()->RemoveLooseGameplayTag(GTag_State_Walking);
	}
	
	if (OwningAIController.IsValid())
	{
		OwningAIController->ReceiveMoveCompleted.RemoveDynamic(this, &UMoveUnitAbilityTask::MoveCompleted);
		OwningAIController->StopMovement();
	}
	
	Super::OnDestroy(bInOwnerFinished);
}

void UMoveUnitAbilityTask::Activate()
{
	Super::Activate();

	if (!IsValid() || !GetWorld())
	{
		FinishExecution(false);
		return;
	}
	
	if (OwningUnit.IsValid())
	{
		OwningUnit->GetAbilitySystemComponent()->AddLooseGameplayTag(GTag_State_Walking);
	}

	OwningAIController->ReceiveMoveCompleted.AddDynamic(this, &UMoveUnitAbilityTask::MoveCompleted);
	if (TargetActor.IsValid())
	{
		OwningAIController->MoveToActor(TargetActor.Get(), TargetActor->GetSimpleCollisionRadius());
	}
	else
	{
		OwningAIController->MoveToLocation(TargetLocation);
	}
}

void UMoveUnitAbilityTask::UpdateTargets(AActor* NewTargetActor, FVector NewTargetLocation)
{
	OwningAIController->ReceiveMoveCompleted.RemoveDynamic(this, &UMoveUnitAbilityTask::MoveCompleted);
	
	if (NewTargetActor)
	{
		TargetActor = NewTargetActor;
		OwningAIController->MoveToActor(TargetActor.Get(), TargetActor->GetSimpleCollisionRadius());
	}
	else if (NewTargetLocation != FVector::ZeroVector)
	{
		TargetLocation = NewTargetLocation;
		OwningAIController->MoveToLocation(TargetLocation);
	}
	
	OwningAIController->ReceiveMoveCompleted.AddDynamic(this, &UMoveUnitAbilityTask::MoveCompleted);
}

void UMoveUnitAbilityTask::MoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	FinishExecution(Result == EPathFollowingResult::Type::Success);
}

void UMoveUnitAbilityTask::FinishExecution(const bool bSuccessful)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (bSuccessful)
		{
			OnTargetReached.Broadcast();
		}
		else if (bCancelAbilityOnFailed)
		{
			Ability->CancelAbility(Ability->GetCurrentAbilitySpecHandle(), Ability->GetCurrentActorInfo(),
				Ability->GetCurrentActivationInfo(), true);	
		}
		else
		{
			OnFailed.Broadcast();
		}
	}
	EndTask();
}

bool UMoveUnitAbilityTask::IsValid()
{
	OwningUnit = Cast<AUnitBase>(GetOwnerActor());
	if (!OwningUnit.IsValid())
	{
		UE_LOG(LogScript, Error, TEXT("%s was called without an owning Pawn"), *this->GetName());

		return false;
	}
		
	OwningAIController = OwningUnit->GetController<AAIController>();
	if (!OwningAIController.IsValid())
	{
		UE_LOG(LogScript, Error, TEXT("%s was called without an owning AIController"), *this->GetName());
		
		return false;
	}

	if (!TargetActor.IsValid() && TargetLocation == FVector::ZeroVector)
	{
		UE_LOG(LogScript, Error, TEXT("%s was called without a valid target actor or location (0,0,0 is not valid)"), *this->GetName());
		
		return false;	
	}

	return true;
}
