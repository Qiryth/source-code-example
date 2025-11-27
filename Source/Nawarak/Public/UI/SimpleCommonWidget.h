// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SimpleCommonWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NAWARAK_API USimpleCommonWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
	
// Accessors
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetText(const FText& Text);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetImage(UTexture2D* Texture);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResetImage();	
};
