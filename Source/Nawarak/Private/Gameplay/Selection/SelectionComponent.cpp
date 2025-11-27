// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Selection/SelectionComponent.h"

#include "Core/PlayerControllers/CorePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Gameplay/GameplayHUDWidget.h"

USelectionComponent::USelectionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USelectionComponent::ShowWidget()
{
	if (const ACorePlayerController* CorePlayerController = Cast<ACorePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		const TWeakObjectPtr<UGameplayHUDWidget> GameplayHUDWidget = CorePlayerController->GetGameplayHUDWidget();
		if (GameplayHUDWidget.IsValid())
		{
			GameplayHUDWidget->SetSelectionWidget(GetOwner(), SelectionWidgetClass);
		}
	}
}
