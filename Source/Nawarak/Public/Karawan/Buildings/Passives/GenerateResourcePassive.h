// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Karawan/Buildings/Passives/BuildingPassiveBase.h"
#include "Resources/ResourceBase.h"
#include "GenerateResourcePassive.generated.h"

/**
 * 
 */
UCLASS()
class NAWARAK_API UGenerateResourcePassive : public UBuildingPassiveBase
{
	GENERATED_BODY()

	
// Lifecycle
public:
	UGenerateResourcePassive();
	
	virtual void Activate() override;
	virtual void Deactivate() override;


// Functions
private:
	void GenerateResource() const;
	

// Variables
private:
	UPROPERTY(EditAnywhere, Category="Custom", meta=(DisplayAfter="Description"))
	float Interval = 1.0f;
	UPROPERTY(EditAnywhere, Category="Custom", meta=(DisplayAfter="Description"))
	FResourceTuple ResourceAmountTuple;

	FTimerHandle GenerateResourceTimerHandle;
	FTimerDelegate GenerateResourceTimerDelegate;
};
