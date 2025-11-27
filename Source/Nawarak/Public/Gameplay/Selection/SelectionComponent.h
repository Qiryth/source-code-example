// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionComponent.generated.h"


class USelectionWidgetBase;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, PrioritizeCategories="Custom"))
class NAWARAK_API USelectionComponent : public UActorComponent
{
	GENERATED_BODY()


// Lifecycle
public:	
	USelectionComponent();


// Functions
public:
	UFUNCTION(BlueprintCallable)
	void ShowWidget();

// Variables
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USelectionWidgetBase> SelectionWidgetClass;
};
