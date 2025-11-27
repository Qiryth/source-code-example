// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Buildings/BuildingSlotComponent.h"

#include "Karawan/Buildings/BuildingBase.h"
#include "Karawan/Units/UnitBase.h"

UBuildingSlotComponent::UBuildingSlotComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBuildingSlotComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwningUnit = Cast<AUnitBase>(GetOwner());
}

bool UBuildingSlotComponent::ConstructBuilding(const TSubclassOf<ABuildingBase> BuildingClass)
{
	if (Building.IsValid() || !OwningUnit.IsValid() || !GetWorld()) return false;

	const ABuildingBase* CDO = BuildingClass->GetDefaultObject<ABuildingBase>();
	const TWeakObjectPtr<AKarawan> Karawan = OwningUnit->GetKarawan();
	if (!CDO || !Karawan.IsValid() || 
		!Karawan->GetResourceData().TryRemove(CDO->GetConstructionCost())) return false;
	
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (AActor* SpawnedActor = GetWorld()->SpawnActor(BuildingClass, &GetComponentTransform(), ActorSpawnParameters))
	{
		Building = Cast<ABuildingBase>(SpawnedActor);
		if (!Building.IsValid()) return false;
		
		Building->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Building->Init();
		OnBuildingChanged.Broadcast(this);
		return true;
	}
	return false;
}

void UBuildingSlotComponent::DemolishBuilding()
{
	if (Building.IsValid())
	{
		Building->Destroy();
		Building = nullptr;
		OnBuildingChanged.Broadcast(this);
	}
}

TWeakObjectPtr<ABuildingBase> UBuildingSlotComponent::GetBuilding() const
{
	return Building;
}
