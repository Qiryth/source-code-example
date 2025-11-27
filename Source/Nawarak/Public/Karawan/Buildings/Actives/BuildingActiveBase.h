// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingActiveBase.generated.h"

class ABuildingBase;
/**
 * 
 */
UCLASS(Abstract, EditInlineNew, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API UBuildingActiveBase : public UObject
{
	GENERATED_BODY()

// Lifecycle
public:
	virtual void Init(TWeakObjectPtr<ABuildingBase> OwningBuilding);
	virtual void Queue();

protected:
	virtual void Activate() {};
	void FinishActivation() const;


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
