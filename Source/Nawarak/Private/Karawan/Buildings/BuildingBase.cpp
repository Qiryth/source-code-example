// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Buildings/BuildingBase.h"

#include "Core/GameInstance/CoreGameInstance.h"
#include "Gameplay/Selection/SelectionComponent.h"
#include "Karawan/Buildings/Actives/BuildingActiveBase.h"
#include "Karawan/Buildings/Passives/BuildingPassiveBase.h"
#include "Karawan/Units/UnitBase.h"

ABuildingBase::ABuildingBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().NoCollision);
	RootComponent = StaticMeshComponent;
	
	SelectionComponent = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
}

void ABuildingBase::Init()
{
	for (const TObjectPtr<UBuildingPassiveBase>& BuildingPassive : BuildingPassives)
	{
		BuildingPassive->Init(this);
	}

	for (const TObjectPtr<UBuildingActiveBase>& BuildingActive : BuildingActives)
	{
		BuildingActive->Init(this);
	}
}

USelectionComponent* ABuildingBase::GetSelectionComponent() const
{
	return SelectionComponent;
}

TWeakObjectPtr<UTexture2D> ABuildingBase::GetBuildingIcon() const
{
	return BuildingIcon;
}

const FText& ABuildingBase::GetDescription() const
{
	return Description;
}

const TMap<EResourceType, int32>& ABuildingBase::GetConstructionCost() const
{
	return ConstructionCost;
}

TWeakObjectPtr<AUnitBase> ABuildingBase::GetOwningUnit() const
{
	return Cast<AUnitBase>(GetAttachParentActor());
}
