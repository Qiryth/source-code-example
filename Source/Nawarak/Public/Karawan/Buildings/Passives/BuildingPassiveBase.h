// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingPassiveBase.generated.h"

class ABuildingBase;
/**
 * 
 */
UCLASS(Abstract, EditInlineNew, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API UBuildingPassiveBase : public UObject
{
	GENERATED_BODY()


// Lifecycle
public:
	virtual void Init(TWeakObjectPtr<ABuildingBase> OwningBuilding);
	virtual void BeginDestroy() override;
	
	virtual void Activate() {};
	virtual void Deactivate() {};


// Accessors
public:
	const FText& GetDescription();
	
	
// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom")
	FText Description;
	
	TWeakObjectPtr<ABuildingBase> Building;
};
