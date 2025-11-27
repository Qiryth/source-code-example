// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Buildings/Passives/BuildingPassiveBase.h"

void UBuildingPassiveBase::Init(const TWeakObjectPtr<ABuildingBase> OwningBuilding)
{
	if (OwningBuilding.IsValid())
	{
		Building = OwningBuilding;
		Activate();
	}
}

void UBuildingPassiveBase::BeginDestroy()
{
	UObject::BeginDestroy();

	if (Building.IsValid())
	{
		Deactivate();
	}
}

const FText& UBuildingPassiveBase::GetDescription()
{
	return Description;
}
