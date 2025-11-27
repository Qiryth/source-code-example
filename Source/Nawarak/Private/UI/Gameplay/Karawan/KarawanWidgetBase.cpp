// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Gameplay/Karawan/KarawanWidgetBase.h"

#include "Core/PlayerControllers/CorePlayerController.h"
#include "Karawan/Karawan.h"

void UKarawanWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	OwningCorePlayerController = Cast<ACorePlayerController>(GetOwningPlayer());
	if (OwningCorePlayerController.IsValid())
	{
		SetKarawan(OwningCorePlayerController->GetCurrentKarawan());
		OwningCorePlayerController->KarawanChangedDelegate.AddUObject(this, &UKarawanWidgetBase::SetKarawan);
	}
}

void UKarawanWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();

	if (OwningCorePlayerController.IsValid())
	{
		OwningCorePlayerController->KarawanChangedDelegate.RemoveAll(this);
	}
}

void UKarawanWidgetBase::SetKarawan(TWeakObjectPtr<AKarawan> Karawan)
{
	PreKarawanChanged();
	
	TrackedKarawan = Karawan;
	if (!TrackedKarawan.IsValid()) return;
	KarawanChanged();

	PostKarawanChanged();
}
