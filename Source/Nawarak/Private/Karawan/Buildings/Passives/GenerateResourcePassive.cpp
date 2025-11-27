// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Buildings/BuildingBase.h"
#include "Karawan/Buildings/Passives/GenerateResourcePassive.h"
#include "Karawan/Units/UnitBase.h"

UGenerateResourcePassive::UGenerateResourcePassive()
{
	GenerateResourceTimerDelegate.BindUObject(this, &UGenerateResourcePassive::GenerateResource);
}

void UGenerateResourcePassive::Activate()
{
	if (!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(GenerateResourceTimerHandle, GenerateResourceTimerDelegate, Interval, true);
}

void UGenerateResourcePassive::Deactivate()
{
	if (!GetWorld()) return;
	GetWorld()->GetTimerManager().ClearTimer(GenerateResourceTimerHandle);
}

void UGenerateResourcePassive::GenerateResource() const
{
	if (Building.IsValid())
	{
		Building->GetOwningUnit()->GetKarawan()->GetResourceData().Add(ResourceAmountTuple);
	}
}
