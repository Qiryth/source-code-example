// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Gameplay/Selection/FactionObject.h"
#include "CorePlayerState.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API ACorePlayerState : public APlayerState
{
	GENERATED_BODY()


public:
	EFaction Faction = EFaction::Friendly;
};
