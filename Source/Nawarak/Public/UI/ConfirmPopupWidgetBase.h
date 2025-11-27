// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ConfirmPopupWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NAWARAK_API UConfirmPopupWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()


// Functions
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetMessage(const FText& MessageText);
	
	FSimpleDelegate OnConfirm;
	FSimpleDelegate OnCancel;
	
protected:
	UFUNCTION(BlueprintCallable)
	void Confirm() const;
	UFUNCTION(BlueprintCallable)
	void Cancel() const;
};
