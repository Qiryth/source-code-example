// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/GameplayEventAbility.h"

#include "AbilitySystemComponent.h"
#include "Gameplay/GameplayTagDeclarations.h"
#include "Karawan/JobBoard.h"
#include "Karawan/Units/UnitBase.h"

bool FGameplayAbilityTargetData_EndPont::HasEndPoint() const
{
	return true;
}

FVector FGameplayAbilityTargetData_EndPont::GetEndPoint() const
{
	return EndPoint;
}

UGameplayEventAbility::UGameplayEventAbility()
{
	CancelAbilitiesWithTag = FGameplayTagContainer(GTag_Ability);
	
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayEventAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	OwningUnit = Cast<AUnitBase>(ActorInfo->OwnerActor);

	if (OwningUnit.IsValid())
	{
		AnimationMontages = OwningUnit->GetAnimationSlotsForAbility(this->GetClass()).AnimationMontageSlots;
	}
}

void UGameplayEventAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TriggerTag = TriggerEventData->EventTag;
	TargetActor = TriggerEventData->Target;
	TargetResource = Cast<AResourceBase>(TriggerEventData->Target);
	TargetUnit = Cast<AUnitBase>(TriggerEventData->Target);
	
	if (TriggerEventData->TargetData.Get(0) && TriggerEventData->TargetData.Get(0)->HasEndPoint())
	{
		TargetLocation = TriggerEventData->TargetData.Get(0)->GetEndPoint();
	}
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayEventAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (TriggerTag != GTag_Ability_Move && OwningUnit->GetKarawan().IsValid())
	{
		OwningUnit->GetKarawan()->GetJobBoard()->InformJobCompleted(OwningUnit);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#if WITH_EDITOR
void UGameplayEventAbility::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName().ToString() != "AbilityTags") return;

	ActivationOwnedTags = GetAssetTags();

	AbilityTriggers.Empty();
	for (int i = 0; i < ActivationOwnedTags.Num(); ++i)
	{
		FAbilityTriggerData AbilityTriggerData;
		AbilityTriggerData.TriggerTag = ActivationOwnedTags.GetByIndex(i);
		AbilityTriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;	
		AbilityTriggers.Add(AbilityTriggerData);
	}
}
#endif