// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Karawan/Buildings/BuildingBase.h"
#include "ChooseBuildingWidget.generated.h"

class AKarawan;
class ABuildingBase;
class USimpleCommonButton;
class UBuildingSlotComponent;
/**
 * 
 */
UCLASS()
class NAWARAK_API UChooseBuildingWidget : public UCommonUserWidget
{
	GENERATED_BODY()

	
// Statics
public:
	UFUNCTION(BlueprintCallable)
	void ConnectButtonAndBuilding(USimpleCommonButton* SimpleButton, TSubclassOf<ABuildingBase> BuildingClass);


// Functions
	UFUNCTION(BlueprintCallable)
	void SetTrackedBuildingSlot(UBuildingSlotComponent* BuildingSlotComponent);
	
	void ResourceChanged(EResourceType Resource, int32 Amount);
	
	TWeakObjectPtr<UBuildingSlotComponent> TrackedBuildingSlot;
	TWeakObjectPtr<AKarawan> TrackedKarawan;
	TMap<TWeakObjectPtr<USimpleCommonButton>, TWeakObjectPtr<ABuildingBase>> ButtonPerDefaultBuildingBase;
};
