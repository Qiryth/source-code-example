// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SelectionWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class NAWARAK_API USelectionWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()


// Accessors
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetTrackedActor(AActor* Actor) {};
};
