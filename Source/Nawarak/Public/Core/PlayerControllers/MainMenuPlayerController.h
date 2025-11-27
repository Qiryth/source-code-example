// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/ConfirmPopupWidgetBase.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()


// Functions
public:
	UFUNCTION(BlueprintNativeEvent)
	UConfirmPopupWidgetBase* PushPopup(TSubclassOf<UConfirmPopupWidgetBase> Class);
};
