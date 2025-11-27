// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayHUDWidget.generated.h"

class UBuildingSlotComponent;
class USelectionWidgetBase;
class USelectionComponent;
class USelectionInterface;
/**
 * 
 */
UCLASS()
class NAWARAK_API UGameplayHUDWidget : public UCommonUserWidget
{
	GENERATED_BODY()


// Functions
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetSelectionWidget(AActor* SelectedActor, TSubclassOf<USelectionWidgetBase> WidgetClass);
	UFUNCTION(BlueprintImplementableEvent)
	void ShowBuildingWidget(UBuildingSlotComponent* BuildingSlotComponent);
};
