// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MoveUnitAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveUnitAbilityTaskDelegate);

class AAIController;
class AUnitBase;
/**
 * 
 */
UCLASS()
class NAWARAK_API UMoveUnitAbilityTask : public UAbilityTask
{
	GENERATED_BODY()


// Static
public:
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="Move Unit",
	HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UMoveUnitAbilityTask* CreateMoveUnitProxy(UGameplayAbility* OwningAbility, FName TaskInstanceName,
		AActor* TargetActor, FVector TargetLocation = FVector::ZeroVector, bool CancelAbilityOnFailed = true);


// Lifecycle
public:
	UMoveUnitAbilityTask();

	virtual void OnDestroy(bool bInOwnerFinished) override;

protected:
	virtual void Activate() override;


// Functions
public:
	UFUNCTION(BlueprintCallable)
	void UpdateTargets(AActor* NewTargetActor, FVector NewTargetLocation = FVector::ZeroVector);
	
private:
	UFUNCTION()
	void MoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	void FinishExecution(bool bSuccessful);
	bool IsValid();

	
// Variables
public:
	UPROPERTY(BlueprintAssignable)
	FMoveUnitAbilityTaskDelegate OnTargetReached;
	UPROPERTY(BlueprintAssignable)
	FMoveUnitAbilityTaskDelegate OnFailed;
	
private:
	TWeakObjectPtr<AUnitBase> OwningUnit;
	TWeakObjectPtr<AAIController> OwningAIController;
	
	TWeakObjectPtr<AActor> TargetActor = nullptr;
	FVector TargetLocation = FVector::Zero();
	
	bool bCancelAbilityOnFailed = false;
};
