// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayEventAbility.generated.h"

class AResourceBase;
class UJob;
class AUnitBase;

USTRUCT()
struct FGameplayAbilityTargetData_EndPont : public FGameplayAbilityTargetData
{
	       GENERATED_BODY()
	
// Lifecycle
public:
       FGameplayAbilityTargetData_EndPont() {}
       FGameplayAbilityTargetData_EndPont(const FVector& InEndPoint) : EndPoint(InEndPoint) {}

       virtual bool HasEndPoint() const override;
       virtual FVector GetEndPoint() const override;


// Variables
private:
       FVector EndPoint = FVector::Zero();
};

USTRUCT(BlueprintType)
struct FAbilityAnimationSlots
{
	GENERATED_BODY()

// Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UAnimMontage>> AnimationMontageSlots;
};

/**
 * 
 */
UCLASS()
class NAWARAK_API UGameplayEventAbility : public UGameplayAbility
{
	GENERATED_BODY()


// Lifecycle
public:
	UGameplayEventAbility();
	
public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	
// Variables
protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AUnitBase> OwningUnit;
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<const AActor> TargetActor;
	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation = FVector::Zero();

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<const AResourceBase> TargetResource;
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<const AUnitBase> TargetUnit;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UAnimMontage>> AnimationMontages;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag TriggerTag;


#if WITH_EDITOR
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
