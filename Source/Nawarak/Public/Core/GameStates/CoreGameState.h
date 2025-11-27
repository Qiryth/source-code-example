// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CoreGameState.generated.h"

enum class EFaction : uint8;
class UFactionObject;

/**
 * 
 */
UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API ACoreGameState : public AGameStateBase
{
	GENERATED_BODY()


// Accessors
public:
	TWeakObjectPtr<UFactionObject> GetFactionObject(EFaction Faction);
	

// Variables
private:
	TMap<EFaction, TStrongObjectPtr<UFactionObject>> FactionObjects;
};
