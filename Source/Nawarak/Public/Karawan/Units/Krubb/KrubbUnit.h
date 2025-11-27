// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Karawan/Units/UnitBase.h"
#include "KrubbUnit.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NAWARAK_API AKrubbUnit : public AUnitBase
{
	GENERATED_BODY()


// Lifecycle
public:
	AKrubbUnit();
	
	virtual void GiveResourceStack(TWeakObjectPtr<AResourceStack> ResourceStack) override;


// Accessors
	virtual TSubclassOf<UUnitBuildingSlotsWidgetBase> GetBuildingsWidgetClass() override;
	virtual TArray<UBuildingSlotComponent*> GetBuildingSlotComponents() override;
	

// Variables
protected:
	UPROPERTY(EditDefaultsOnly, Category="Custom|UI")
	TSubclassOf<UUnitBuildingSlotsWidgetBase> BuildingsWidgetClass;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBuildingSlotComponent> BuildingSlot_1;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBuildingSlotComponent> BuildingSlot_2;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBuildingSlotComponent> BuildingSlot_3;
};
