// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Gameplay/Selection/BuildingSelectionWidget.h"

#include "Karawan/Buildings/BuildingBase.h"
#include "Karawan/Buildings/Actives/BuildingActiveBase.h"
#include "Karawan/Buildings/Passives/BuildingPassiveBase.h"
#include "UI/SimpleCommonButton.h"
#include "UI/SimpleCommonWidget.h"

void UBuildingSelectionWidget::ConnectButtonAndActive(USimpleCommonButton* SimpleButton, UBuildingActiveBase* BuildingActive)
{
	SimpleButton->SetToolTipText(BuildingActive->GetDescription());
	
	SimpleButton->OnClicked().AddLambda([BuildingActive]()
	{
		BuildingActive->Queue();
	});
}

void UBuildingSelectionWidget::ConnectWidgetAndPassive(USimpleCommonWidget* SimpleWidget, UBuildingPassiveBase* BuildingPassive)
{
	SimpleWidget->SetToolTipText(BuildingPassive->GetDescription());
}

void UBuildingSelectionWidget::SetTrackedActor(AActor* Actor)
{
	TrackedBuilding = Cast<ABuildingBase>(Actor);
	if (TrackedBuilding.IsValid())
	{
		TrackedBuildingUpdated();
	}
}
