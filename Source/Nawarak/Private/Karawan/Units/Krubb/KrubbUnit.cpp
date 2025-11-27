// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Units/Krubb/KrubbUnit.h"

#include "Components/CapsuleComponent.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "Karawan/Buildings/BuildingSlotComponent.h"
#include "Resources/Stacks/ResourceStack.h"

AKrubbUnit::AKrubbUnit()
{
	CapsuleComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().Krubb);
	CapsuleComponent->SetCanEverAffectNavigation(true);
	CapsuleComponent->bDynamicObstacle = false;
	CapsuleComponent->SetAreaClassOverride(nullptr);
	
	BuildingSlot_1 = CreateDefaultSubobject<UBuildingSlotComponent>(TEXT("BuildingSlot_1"));
	BuildingSlot_1->SetupAttachment(SkeletalMeshComponent);
	
	BuildingSlot_2 = CreateDefaultSubobject<UBuildingSlotComponent>(TEXT("BuildingSlot_2"));
	BuildingSlot_2->SetupAttachment(SkeletalMeshComponent);
	
	BuildingSlot_3 = CreateDefaultSubobject<UBuildingSlotComponent>(TEXT("BuildingSlot_3"));
	BuildingSlot_3->SetupAttachment(SkeletalMeshComponent);
}

void AKrubbUnit::GiveResourceStack(const TWeakObjectPtr<AResourceStack> ResourceStack)
{
	Super::GiveResourceStack(ResourceStack);

	if (ResourceStack.IsValid())
	{
		ResourceStack->GetResourceData().MergeInto(Karawan->GetResourceData());
	}
}

TSubclassOf<UUnitBuildingSlotsWidgetBase> AKrubbUnit::GetBuildingsWidgetClass()
{
	return BuildingsWidgetClass;
}

TArray<UBuildingSlotComponent*> AKrubbUnit::GetBuildingSlotComponents()
{
	return {BuildingSlot_1, BuildingSlot_2, BuildingSlot_3};
}
