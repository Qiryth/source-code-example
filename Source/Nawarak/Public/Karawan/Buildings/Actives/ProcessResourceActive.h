// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Karawan/Buildings/Actives/BuildingActiveBase.h"
#include "ProcessResourceActive.generated.h"

enum class EResourceType : uint8;
struct FResourceTuple;
/**
 * 
 */
UCLASS()
class NAWARAK_API UProcessResourceActive : public UBuildingActiveBase
{
	GENERATED_BODY()

	
// Lifecycle
public:
	UProcessResourceActive();
	
protected:
	virtual void Activate() override;


// Functions
private:
	void ProcessResource() const;
	

// Variables
private:
	UPROPERTY(EditAnywhere, Category="Custom", meta=(DisplayAfter="Description"))
	float Duration;
	UPROPERTY(EditAnywhere, Category="Custom", meta=(DisplayAfter="Description"))
	TMap<EResourceType, int32> ResourceCost;
	UPROPERTY(EditAnywhere, Category="Custom", meta=(DisplayAfter="Description"))
	TMap<EResourceType, int32> ResourceProduction;

	FTimerHandle ProcessResourceTimerHandle;
	FTimerDelegate ProcessResourceTimerDelegate;
};
