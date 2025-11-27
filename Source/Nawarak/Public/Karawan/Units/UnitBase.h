// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Gameplay/Selection/SelectionInterface.h"
#include "Karawan/Karawan.h"
#include "UnitBase.generated.h"

class UBuildingSlotComponent;
class UUnitBuildingSlotsWidgetBase;
struct FAbilityAnimationSlots;

UENUM(BlueprintType)
enum class EUnitAnimationState : uint8
{
	Buried,
	Idle,
	Walk,
	Walk_Item,
	Walk_Resource
};

USTRUCT()
struct FBuildingSlotComponentData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UBuildingSlotComponent*> BuildingSlotComponents;
};

struct FGameplayTagContainer;
struct FGameplayTag;
class AResourceStack;
class UArrowComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;
class UGameplayAbility;
class UStateTreeComponent;
class UUnitMovementComponent;

UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API AUnitBase : public APawn, public IAbilitySystemInterface, public ISelectionInterface
{
	GENERATED_BODY()

	friend void AKarawan::RegisterUnit(const TWeakObjectPtr<AUnitBase> Unit);
	friend void AKarawan::UnregisterUnit(const TWeakObjectPtr<AUnitBase> Unit);
	
// Lifecycle
public:
	AUnitBase();

protected:
	virtual void BeginPlay() override;


// Functions
public:
	virtual bool HasBuildingSlots() { return GetBuildingsWidgetClass() != nullptr; };
	virtual bool HasResourceStack() { return false; }
	virtual void GiveResourceStack(TWeakObjectPtr<AResourceStack> ResourceStack) {}
	virtual TWeakObjectPtr<AResourceStack> TakeResourceStack() { return nullptr; }

	bool HasAbilityWithTag(FGameplayTag GameplayTag) const;

private:
	void GameplayTagsChanged(FGameplayTag GameplayTag, int Count);

	
// Accessors
public:
	UFUNCTION(BlueprintPure)
	virtual TSubclassOf<UUnitBuildingSlotsWidgetBase> GetBuildingsWidgetClass() { return nullptr; };
	UFUNCTION(BlueprintPure)
	virtual TArray<UBuildingSlotComponent*> GetBuildingSlotComponents() { return {}; };
	
	virtual FVector GetNavAgentLocation() const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual USelectionComponent* GetSelectionComponent() const override;

	FAbilityAnimationSlots GetAnimationSlotsForAbility(TSubclassOf<UGameplayAbility> AbilityClass);
	TWeakObjectPtr<AKarawan> GetKarawan() const;
	
	float GetMovementSpeed() const;
	float GetRotationSpeed() const;


	
// Variables
protected:
	UPROPERTY(Transient)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USelectionComponent> SelectionComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStateTreeComponent> StateTreeComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UUnitMovementComponent> UnitMovementComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UArrowComponent> ForwardArrow;

	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float MovementSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	float RotationSpeed = 3.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	TMap<TSubclassOf<UGameplayAbility>, FAbilityAnimationSlots> Abilities;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AKarawan> Karawan;
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	EUnitAnimationState UnitAnimationState = EUnitAnimationState::Idle;

	FName CollisionProfileName;
};
