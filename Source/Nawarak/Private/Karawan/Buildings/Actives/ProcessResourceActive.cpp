// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Buildings/Actives/ProcessResourceActive.h"

#include "Karawan/Buildings/BuildingBase.h"
#include "Karawan/Units/UnitBase.h"

UProcessResourceActive::UProcessResourceActive()
{
	ProcessResourceTimerDelegate.BindUObject(this, &UProcessResourceActive::ProcessResource);
}

void UProcessResourceActive::Activate()
{
	if (!Building.IsValid() || !Building->GetOwningUnit().IsValid() ||
		!Building->GetOwningUnit()->GetKarawan()->GetResourceData().TryRemove(ResourceCost)) return FinishActivation();
	
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ProcessResourceTimerHandle, ProcessResourceTimerDelegate, Duration, false);
	}
}

void UProcessResourceActive::ProcessResource() const
{
	if (!Building.IsValid() || !Building->GetOwningUnit().IsValid()) return FinishActivation();

	Building->GetOwningUnit()->GetKarawan()->GetResourceData().Add(ResourceProduction);
	FinishActivation();
}
