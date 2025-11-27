// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Units/UnitBase.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StateTreeComponent.h"
#include "Core/GameInstance/BlueprintReferences.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Gameplay/GameplayTagDeclarations.h"
#include "Gameplay/Abilities/GameplayEventAbility.h"
#include "Gameplay/Selection/SelectionComponent.h"
#include "Helpers/NavArea_Unit.h"
#include "Karawan/Units/UnitMovementComponent.h"

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCanEverAffectNavigation(true);
	CapsuleComponent->bDynamicObstacle = true;
	CapsuleComponent->SetAreaClassOverride(UNavArea_Unit::StaticClass());
	CapsuleComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().Unit);
	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	RootComponent = CapsuleComponent;

	UnitMovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(TEXT("UnitMovementComponent"));
	UnitMovementComponent->bAutoRegisterUpdatedComponent = true;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().NoCollision);
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	ForwardArrow->ArrowColor = FColor::White;
	ForwardArrow->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	for (const FGameplayTag& GameplayTag : TArray<FGameplayTag>{GTag_State_Walking})
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTag).AddUObject(this, &AUnitBase::GameplayTagsChanged);
	}
	
	SelectionComponent = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"));
	StateTreeComponent->SetStartLogicAutomatically(false);

	Abilities.Add(UCoreGameInstance::GetBlueprintReferences().Get_GA_Move());
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();

	UnitMovementComponent->MaxSpeed = MovementSpeed;
	CollisionProfileName = CapsuleComponent->GetCollisionProfileName();
	
	for (auto& [Ability, _] : Abilities)
	{
		AbilitySystemComponent->GiveAbility(Ability);
	}
}

bool AUnitBase::HasAbilityWithTag(const FGameplayTag GameplayTag) const
{
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	AbilitySystemComponent->FindAllAbilitiesWithTags(AbilitySpecHandles, FGameplayTagContainer(GameplayTag));
	return AbilitySpecHandles.Num() > 0;
}

void AUnitBase::GameplayTagsChanged(const FGameplayTag GameplayTag, const int Count)
{
	if (GameplayTag == GTag_State_Walking)
	{
		UnitAnimationState = Count > 0 ? EUnitAnimationState::Walk : EUnitAnimationState::Idle;
	}
	else return;

	CapsuleComponent->SetCanEverAffectNavigation(UnitAnimationState == EUnitAnimationState::Idle);
	CapsuleComponent->SetCollisionProfileName(UnitAnimationState == EUnitAnimationState::Idle ?
		CollisionProfileName : UCoreGameInstance::GetCollisionProfiles().Unit_Walking);

	if (HasResourceStack())
	{
		UnitAnimationState = UnitAnimationState == EUnitAnimationState::Walk ? EUnitAnimationState::Walk_Resource : EUnitAnimationState::Idle;
	}
}

FVector AUnitBase::GetNavAgentLocation() const
{
	return GetActorLocation() - FVector(0, 0, CapsuleComponent->GetScaledCapsuleHalfHeight());
}

UAbilitySystemComponent* AUnitBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USelectionComponent* AUnitBase::GetSelectionComponent() const
{
	return SelectionComponent;
}

float AUnitBase::GetMovementSpeed() const
{
	return MovementSpeed;
}

float AUnitBase::GetRotationSpeed() const
{
	return RotationSpeed;
}

FAbilityAnimationSlots AUnitBase::GetAnimationSlotsForAbility(TSubclassOf<UGameplayAbility> AbilityClass)
{
	return Abilities.FindOrAdd(AbilityClass);
}

TWeakObjectPtr<AKarawan> AUnitBase::GetKarawan() const
{
	return Karawan;
}
