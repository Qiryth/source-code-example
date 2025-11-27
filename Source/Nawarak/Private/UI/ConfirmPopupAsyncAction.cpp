// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ConfirmPopupAsyncAction.h"

#include "Core/PlayerControllers/MainMenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ConfirmPopupWidgetBase.h"

UConfirmPopupAsyncAction* UConfirmPopupAsyncAction::CreateConfirmPopup(UObject* WorldContextObject, FText Message, const TSubclassOf<UConfirmPopupWidgetBase> PopupClass)
{
	UConfirmPopupAsyncAction* NewAsyncTask = NewObject<UConfirmPopupAsyncAction>();

	NewAsyncTask->PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	NewAsyncTask->RegisterWithGameInstance(WorldContextObject);
	NewAsyncTask->PopupClass = PopupClass;
	NewAsyncTask->Message = Message;

	return NewAsyncTask;
}

void UConfirmPopupAsyncAction::Activate()
{
	if (AMainMenuPlayerController* MainMenuPlayerController = Cast<AMainMenuPlayerController>(PlayerController))
	{
		Popup = MainMenuPlayerController->PushPopup(PopupClass);
		Popup->SetMessage(Message);
	}
	else
	{
		return;
	}

	TWeakObjectPtr<UConfirmPopupAsyncAction> WeakThis = this;
	Popup->OnConfirm.BindLambda([WeakThis]()
	{
		if (WeakThis.IsValid())
		{
			WeakThis->Confirm.Broadcast();
			WeakThis->SetReadyToDestroy();
		}
	});
	Popup->OnCancel.BindLambda([WeakThis]()
	{
		if (WeakThis.IsValid())
		{
			WeakThis->Cancel.Broadcast();
			WeakThis->SetReadyToDestroy();
		}
	});
}
