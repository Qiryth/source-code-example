// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Gameplay/Karawan/Buildings/UnitBuildingSlotsWidgetBase.h"

#include "Core/PlayerControllers/CorePlayerController.h"
#include "Gameplay/Selection/SelectionComponent.h"
#include "Karawan/Buildings/BuildingSlotComponent.h"
#include "Karawan/Units/UnitBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SimpleCommonButton.h"
#include "UI/Gameplay/GameplayHUDWidget.h"

void UUnitBuildingSlotsWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	for (UCommonButtonBase* BuildingSlotButton : BuildingSlotButtons)
	{
		BuildingSlotButton->OnClicked().AddLambda([this, BuildingSlotButton]()
		{
			ResolveButtonPress(BuildingSlotButton);
		});
	}
}

void UUnitBuildingSlotsWidgetBase::SetUnit(AUnitBase* Unit)
{
	if (TrackedUnit.IsValid() && TrackedUnit->HasBuildingSlots())
	{
		for (UBuildingSlotComponent* BuildingSlotComponent : TrackedUnit->GetBuildingSlotComponents())
		{
			BuildingSlotComponent->OnBuildingChanged.RemoveDynamic(this, &UUnitBuildingSlotsWidgetBase::BuildingChanged);
		}
	}
	
	TrackedUnit = Unit;
	if (!TrackedUnit.IsValid() || !TrackedUnit->HasBuildingSlots()) return;
	
	for (UBuildingSlotComponent* BuildingSlotComponent : TrackedUnit->GetBuildingSlotComponents())
	{
		BuildingSlotComponent->OnBuildingChanged.AddDynamic(this, &UUnitBuildingSlotsWidgetBase::BuildingChanged);
	}
}

void UUnitBuildingSlotsWidgetBase::BuildingChanged(UBuildingSlotComponent* BuildingSlotComponent)
{
	if (!TrackedUnit.IsValid() || !TrackedUnit->HasBuildingSlots()) return;
	
	const int32 Index = TrackedUnit->GetBuildingSlotComponents().IndexOfByKey(BuildingSlotComponent);
	if (Index == INDEX_NONE || !BuildingSlotButtons.IsValidIndex(Index)) return;
	
	const TWeakObjectPtr<ABuildingBase> Building = BuildingSlotComponent->GetBuilding();
	if (Building.IsValid())
	{
		BuildingSlotButtons[Index]->SetImage(BuildingSlotComponent->GetBuilding()->GetBuildingIcon().Get());
	}
	else
	{
		BuildingSlotButtons[Index]->ResetImage();
	}
	
}

void UUnitBuildingSlotsWidgetBase::ResolveButtonPress(UCommonUserWidget* PressedButton) const
{
	if (!TrackedUnit.IsValid() || !TrackedUnit->HasBuildingSlots()) return;

	const int32 Index = BuildingSlotButtons.IndexOfByKey(PressedButton);
	if (Index == INDEX_NONE || !TrackedUnit->GetBuildingSlotComponents().IsValidIndex(Index)) return;
	
	const TWeakObjectPtr<ABuildingBase> Building = TrackedUnit->GetBuildingSlotComponents()[Index]->GetBuilding();
	if (Building.IsValid())
	{
		Building->GetSelectionComponent()->ShowWidget();
	}
	else if (ACorePlayerController* CorePlayerController = Cast<ACorePlayerController>(GetOwningPlayer()))
	{
		CorePlayerController->GetGameplayHUDWidget()->ShowBuildingWidget(TrackedUnit->GetBuildingSlotComponents()[Index]);
	}
}
