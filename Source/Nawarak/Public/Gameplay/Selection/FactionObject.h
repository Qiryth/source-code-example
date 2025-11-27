// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactionObject.generated.h"

class AKarawan;
class AUnitBase;

UENUM(BlueprintType)
enum class EFaction : uint8
{
	None,
	Hostile,
	Neutral,
	Friendly,
	Wildlife
};

/**
 * 
 */
UCLASS(meta=(PrioritizeCategories="Custom"))
class NAWARAK_API UFactionObject : public UObject
{
	GENERATED_BODY()


// Functions
public:
	void RegisterKarawan(TWeakObjectPtr<AKarawan> Karawan);


// Accessors
public:
	TWeakObjectPtr<AKarawan> GetNextKarawan();
	
	
// Variables
private:
	TArray<TWeakObjectPtr<AKarawan>> Karawans;

	int CurrentKarawanIndex = -1;
};
