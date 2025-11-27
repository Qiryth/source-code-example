// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BuildingSlotComponent.generated.h"

class AUnitBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingChanged, UBuildingSlotComponent*, BuildingSlotComponent);

class ABuildingBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAWARAK_API UBuildingSlotComponent : public USceneComponent
{
	GENERATED_BODY()


// Lifecycle
public:	
	UBuildingSlotComponent();

	virtual void BeginPlay() override;

// Functions
public:
	UFUNCTION(BlueprintCallable)
	bool ConstructBuilding(TSubclassOf<ABuildingBase> BuildingClass);
	UFUNCTION(BlueprintCallable)
	void DemolishBuilding();


// Accessors
public:
	TWeakObjectPtr<ABuildingBase> GetBuilding() const;
	

// Variables
public:
	FBuildingChanged OnBuildingChanged;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ABuildingBase> Building;
	
private:
	TWeakObjectPtr<AUnitBase> OwningUnit;
};
