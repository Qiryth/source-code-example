// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Gameplay/Karawan/Buildings/ChooseBuildingWidget.h"

#include "Core/PlayerControllers/CorePlayerController.h"
#include "Karawan/Karawan.h"
#include "Karawan/Buildings/BuildingBase.h"
#include "Karawan/Buildings/BuildingSlotComponent.h"
#include "UI/SimpleCommonButton.h"

void UChooseBuildingWidget::ConnectButtonAndBuilding(USimpleCommonButton* SimpleButton, TSubclassOf<ABuildingBase> BuildingClass)
{
	if (!SimpleButton || !BuildingClass) return;

	const TWeakObjectPtr<ABuildingBase> ClassDefaultObject = BuildingClass->GetDefaultObject<ABuildingBase>();
	if (!ClassDefaultObject.IsValid()) return;
	
	ButtonPerDefaultBuildingBase.Add(SimpleButton, ClassDefaultObject);
	
	SimpleButton->SetImage(ClassDefaultObject->GetBuildingIcon().Get());
	SimpleButton->SetToolTipText(ClassDefaultObject->GetDescription());
	SimpleButton->OnClicked().AddLambda([this, BuildingClass]()
	{
		if (TrackedBuildingSlot.IsValid() && TrackedBuildingSlot->ConstructBuilding(BuildingClass))
		{
			RemoveFromParent();
		}
	});
	
	if (!TrackedKarawan.IsValid()) return;
	if (!TrackedKarawan->GetResourceData().Contains(ClassDefaultObject->GetConstructionCost()))
	{
		SimpleButton->LockButton();
	}
}

void UChooseBuildingWidget::SetTrackedBuildingSlot(UBuildingSlotComponent* BuildingSlotComponent)
{
	TrackedBuildingSlot = BuildingSlotComponent;
	TrackedKarawan = Cast<ACorePlayerController>(GetOwningPlayer())->GetCurrentKarawan();
	TrackedKarawan->GetResourceData().OnResourceChangedDelegate.AddUObject(this, &UChooseBuildingWidget::ResourceChanged);
}

void UChooseBuildingWidget::ResourceChanged(EResourceType Resource, int32 Amount)
{
	if (!TrackedKarawan.IsValid()) return;
	
	for (auto& [Button, ClassDefaultObject] : ButtonPerDefaultBuildingBase)
	{
		if (!Button.IsValid() || !ClassDefaultObject.IsValid()) continue;
		
		if (TrackedKarawan->GetResourceData().Contains(ClassDefaultObject->GetConstructionCost()))
		{
			Button->UnlockButton();
		}
		else
		{
			Button->LockButton();
		}
	}
}
