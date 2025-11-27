// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Karawan/Buildings/BuildingBase.h"
#include "UnitBuildingSlotsWidgetBase.generated.h"

class USimpleCommonButton;
class UBuildingSlotComponent;
class AUnitBase;

/**
 * 
 */
UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API UUnitBuildingSlotsWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()


// Lifecycle
protected:
	virtual void NativeConstruct() override;

	
// Functions
protected:
	UFUNCTION(BlueprintCallable)
	void SetUnit(AUnitBase* Unit);
	UFUNCTION()
	void BuildingChanged(UBuildingSlotComponent* BuildingSlotComponent);
	void ResolveButtonPress(UCommonUserWidget* PressedButton) const;


// Variables
protected:
	UPROPERTY(EditAnywhere, Category="Temp")
	TSubclassOf<ABuildingBase> BuildingClassTemp;
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AUnitBase> TrackedUnit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Custom")
	TArray<USimpleCommonButton*> BuildingSlotButtons;
};
