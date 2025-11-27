// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "JobBoard.generated.h"

class AKarawan;
class AResourceBase;
class AUnitBase;

USTRUCT()
struct FJob
{
	GENERATED_BODY()

	static FJob CreateGatherJob(TWeakObjectPtr<AResourceBase> ResourceBase);

	bool operator==(const FJob& Other) const { return TargetActor == Other.TargetActor && AbilityTag == Other.AbilityTag; }


// Lifecycle
	FJob() {}
	FJob(const FGameplayTag InAbilityTag, const TWeakObjectPtr<AActor> InTargetActor, const int32 InAssignmentCapacity = 1) :
		AbilityTag(InAbilityTag), TargetActor(InTargetActor), AssignmentCapacity(InAssignmentCapacity) {}


// Functions
	bool CanBeAssigned() const;
	bool IsAssigned() const { return AssignedUnits.Num() > 0; }
	bool IsFullyAssigned() const { return AssignedUnits.Num() >= AssignmentCapacity; }

	
// Variables
	UPROPERTY(Transient, VisibleAnywhere)
	FGameplayTag AbilityTag;
	UPROPERTY(Transient, VisibleAnywhere)
	TWeakObjectPtr<AActor> TargetActor;
	UPROPERTY(Transient, VisibleAnywhere)
	TSet<TWeakObjectPtr<AUnitBase>> AssignedUnits;
	
private:
	UPROPERTY(Transient, VisibleAnywhere)
	int32 AssignmentCapacity = 1;
	
	TFunction<bool()> AssignementConditionsPredicate;
};


UCLASS(meta=(PrioritizeCategories="Custom"))
class NAWARAK_API UJobBoard : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJobBoard();
	
// Lifecycle
public:
	virtual void BeginPlay() override;


// Functions
public:
	bool AssignUnitToJob(TWeakObjectPtr<AUnitBase> Unit);
	void InformJobCompleted(TWeakObjectPtr<AUnitBase> Unit);
	
private:
	UFUNCTION()
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	
// Variables
private:
	UPROPERTY(EditAnywhere, Category="Custom", meta=(Categories="_Ability"))
	FGameplayTagContainer ListJobsForTheseAbilityTags;

	UPROPERTY(Transient, VisibleAnywhere, Category="Custom")
	TArray<FJob> Jobs;
	
	TWeakObjectPtr<AKarawan> OwningKarawan;
};
