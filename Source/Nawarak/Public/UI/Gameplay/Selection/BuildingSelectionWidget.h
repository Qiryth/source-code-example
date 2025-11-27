// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectionWidgetBase.h"
#include "BuildingSelectionWidget.generated.h"

class USimpleCommonWidget;
class UBuildingPassiveBase;
class UBuildingActiveBase;
class USimpleCommonButton;
class UHorizontalBox;
class ABuildingBase;
/**
 * 
 */
UCLASS()
class NAWARAK_API UBuildingSelectionWidget : public USelectionWidgetBase
{
	GENERATED_BODY()

	
// Static
protected:
	UFUNCTION(BlueprintCallable)
	static void ConnectButtonAndActive(USimpleCommonButton* SimpleButton, UBuildingActiveBase* BuildingActive);
	UFUNCTION(BlueprintCallable)
	static void ConnectWidgetAndPassive(USimpleCommonWidget* SimpleWidget, UBuildingPassiveBase* BuildingPassive);

	
// Functions
public:
	UFUNCTION(BlueprintImplementableEvent)
	void TrackedBuildingUpdated();
	
	
// Accessors
public:
	virtual void SetTrackedActor(AActor* Actor) override;


// Variables
protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ABuildingBase> TrackedBuilding;
};
