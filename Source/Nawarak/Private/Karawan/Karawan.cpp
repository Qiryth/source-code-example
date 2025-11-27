// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Karawan.h"

#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StateTreeComponent.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "Core/GameStates/CoreGameState.h"
#include "Gameplay/Selection/FactionObject.h"
#include "Karawan/JobBoard.h"
#include "Karawan/Units/UnitBase.h"
#include "Resources/ResourceBase.h"
#include "UI/Gameplay/Karawan/Buildings/UnitBuildingSlotsWidgetBase.h"


AKarawan::AKarawan()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().Karawan);
	SphereComponent->CanCharacterStepUpOn = ECB_No;
	SphereComponent->SetSphereRadius(1000);
	RootComponent = SphereComponent;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	JobBoard = CreateDefaultSubobject<UJobBoard>(TEXT("JobBoard"));
}

void AKarawan::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	if (UWorld* World = GetWorld())
	{
		if (AActor* SpawnedActor = World->SpawnActor(KarawanData.LeadUnit, &GetActorTransform(), ActorSpawnParameters))
		{
			RegisterLeadUnit(static_cast<AUnitBase*>(SpawnedActor));
		}

		FTransform Transform = GetActorTransform();
		Transform.SetLocation(Transform.GetLocation() - GetActorForwardVector() * 500);

		for (auto [UnitClass, Amount] : KarawanData.Units)
		{
			for (int i = 0; i < Amount; ++i)
			{
				if (AActor* SpawnedActor = World->SpawnActor(UnitClass, &Transform, ActorSpawnParameters))
				{
					RegisterUnit(static_cast<AUnitBase*>(SpawnedActor));
				}	
			}
		}
	}
}

void AKarawan::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (const UWorld* World = GetWorld())
	{
		if (ACoreGameState* GameState = World->GetGameState<ACoreGameState>())
		{
			GameState->GetFactionObject(KarawanData.Faction)->RegisterKarawan(this);
		}
	}
}

UAbilitySystemComponent* AKarawan::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AKarawan::RegisterUnit(const TWeakObjectPtr<AUnitBase> Unit)
{
	if (Unit->Karawan.IsValid())
	{
		if (Unit->Karawan == this) return;

		Unit->Karawan->UnregisterUnit(Unit);
	}

	Units.Add(Unit);
	Unit->Karawan = this;
	Unit->StateTreeComponent->StartLogic();
}

void AKarawan::UnregisterUnit(const TWeakObjectPtr<AUnitBase> Unit)
{
	Unit->StateTreeComponent->StopLogic(TEXT("Unit left Karawan"));
	Unit->Karawan = nullptr;
	Units.Remove(Unit);
}

void AKarawan::RegisterLeadUnit(const TWeakObjectPtr<AUnitBase> Unit)
{
	RegisterUnit(Unit);
	LeadUnit = Unit;
	AttachToActor(LeadUnit.Get(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AKarawan::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AResourceBase* OtherResource = Cast<AResourceBase>(OtherActor))
	{
		ResourcesInRange.Add(OtherResource);
	}
}

void AKarawan::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AResourceBase* OtherResource = Cast<AResourceBase>(OtherActor))
	{
		ResourcesInRange.Remove(OtherResource);
	}
}

TArray<AUnitBase*> AKarawan::GetUnitsWithBuildingSlots()
{
	TArray<AUnitBase*> UnitsWithBuildingSlots;
	
	for (TWeakObjectPtr<AUnitBase> Unit : Units)
	{
		if (Unit.IsValid() && Unit->GetBuildingsWidgetClass())
		{
			UnitsWithBuildingSlots.Add(Unit.Get());
		}
	}
	
	return UnitsWithBuildingSlots;
}

TWeakObjectPtr<UJobBoard> AKarawan::GetJobBoard()
{
	return JobBoard;
}

TWeakObjectPtr<AUnitBase> AKarawan::GetLeadUnit() const
{
	return LeadUnit;
}

FResourceData& AKarawan::GetResourceData()
{
	return KarawanData.ResourceData;
}
