// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "SimpleCommonButton.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NAWARAK_API USimpleCommonButton : public UCommonButtonBase
{
	GENERATED_BODY()


// Accessors
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetText(const FText& ButtonText);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetImage(UTexture2D* Texture);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResetImage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LockButton();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UnlockButton();
};
