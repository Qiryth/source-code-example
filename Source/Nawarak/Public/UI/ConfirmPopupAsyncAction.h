// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ConfirmPopupAsyncAction.generated.h"

class UConfirmPopupWidgetBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConfirmPopupDelegate);

/**
 * 
 */
UCLASS(meta = (ExposedAsyncProxy=AsyncAction))
class NAWARAK_API UConfirmPopupAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	
// Static
public:
	UFUNCTION(BlueprintCallable, DisplayName="Confirm Popup", meta = (BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"))
	static UConfirmPopupAsyncAction* CreateConfirmPopup(UObject* WorldContextObject, FText Message, TSubclassOf<UConfirmPopupWidgetBase> PopupClass);


// Lifecycle
public:
	virtual void Activate() override;

	
// Variables
protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UConfirmPopupWidgetBase> Popup;

private:
	UPROPERTY(BlueprintAssignable)
	FConfirmPopupDelegate Confirm;
	UPROPERTY(BlueprintAssignable)
	FConfirmPopupDelegate Cancel;

	TWeakObjectPtr<APlayerController> PlayerController;
	TSubclassOf<UConfirmPopupWidgetBase> PopupClass;
	FText Message;
};
