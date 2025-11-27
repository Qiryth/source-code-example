// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/ResourceBase.h"
#include "UI/Gameplay/Karawan/KarawanWidgetBase.h"
#include "KarawanResourcesWidget.generated.h"

class ACorePlayerController;
class AKarawan;
/**
 * 
 */
UCLASS()
class NAWARAK_API UKarawanResourcesWidget : public UKarawanWidgetBase
{
	GENERATED_BODY()


// Lifecycle
protected:
	virtual void PreKarawanChanged() override;
	virtual void PostKarawanChanged() override;


// Functions
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ResourceChanged(EResourceType ResourceType, int Count);
};
