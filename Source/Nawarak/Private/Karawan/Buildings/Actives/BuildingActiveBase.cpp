// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Buildings/Actives/BuildingActiveBase.h"

#include "Karawan/Buildings/BuildingBase.h"

void UBuildingActiveBase::Init(const TWeakObjectPtr<ABuildingBase> OwningBuilding)
{
	if (OwningBuilding.IsValid())
	{
		Building = OwningBuilding;
	}
}

void UBuildingActiveBase::Queue()
{
	if (!Building.IsValid()) return;

	if (Building->CurrentBuildingActive.IsValid())
	{
		Building->BuildingActiveQueue.Add(this);
	}
	else
	{
		Building->CurrentBuildingActive = this;
		Activate();
	}
}

void UBuildingActiveBase::FinishActivation() const
{
	if (!Building.IsValid()) return;

	if (Building->BuildingActiveQueue.IsEmpty())
	{
		Building->CurrentBuildingActive.Reset();
		return;
	}
	
	Building->CurrentBuildingActive = Building->BuildingActiveQueue[0];
	Building->BuildingActiveQueue.RemoveAt(0);
	
	if (Building->CurrentBuildingActive.IsValid())
	{
		Building->CurrentBuildingActive->Activate();
	}
	else
	{
		FinishActivation();
	}
}

const FText& UBuildingActiveBase::GetDescription()
{
	return Description;
}
