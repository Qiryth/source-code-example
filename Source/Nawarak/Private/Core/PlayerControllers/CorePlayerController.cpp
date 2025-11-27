// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerControllers/CorePlayerController.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Core/GameInstance/BlueprintReferences.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "Core/GameStates/CoreGameState.h"
#include "Core/PlayerControllers/CorePlayerControllerPawn.h"
#include "Core/PlayerStates/CorePlayerState.h"
#include "Gameplay/GameplayTagDeclarations.h"
#include "Gameplay/Abilities/GameplayEventAbility.h"
#include "Gameplay/Selection/SelectionInterface.h"
#include "Karawan/Karawan.h"
#include "Resources/ResourceBase.h"
#include "UI/Gameplay/GameplayHUDWidget.h"
#include "UserSettings/EnhancedInputUserSettings.h"

ACorePlayerController::ACorePlayerController()
{
	bShowMouseCursor = true;
}

void ACorePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputModeGameAndUI);
	
	SetControlRotation({-CameraBasePitch, 0, 0});

	if (UWorld* World = GetWorld())
	{
		if (ACoreGameState* CoreGameState = World->GetGameState<ACoreGameState>())
		{
			CurrentFactionObject = CoreGameState->GetFactionObject(GetPlayerState<ACorePlayerState>()->Faction);
			if (!CurrentFactionObject.IsValid()) return;

			CurrentKarawan = CurrentFactionObject->GetNextKarawan();
			if (!CurrentKarawan.IsValid()) return;

			GetPawn()->SetActorLocation(CurrentKarawan->GetActorLocation());
			HUD = CreateWidget(this, UCoreGameInstance::GetBlueprintReferences().Get_WBP_GameplayHUD());
			HUD->AddToViewport();
		}
	}
}

void ACorePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (UEnhancedInputUserSettings* UserSettings = Subsystem->GetUserSettings())
		{
			UserSettings->RegisterInputMappingContext(MappingContext);
		}

		FModifyContextOptions ModifyContextOptions = {};
		ModifyContextOptions.bNotifyUserSettings = true;

		Subsystem->AddMappingContext(MappingContext, 0, ModifyContextOptions);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(CameraPanAction, ETriggerEvent::Triggered, this, &ACorePlayerController::CameraPanTriggered);
		EnhancedInputComponent->BindAction(CameraRotateAction, ETriggerEvent::Triggered, this, &ACorePlayerController::CameraRotateTriggered);
		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &ACorePlayerController::CommandCompleted);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ACorePlayerController::SelectCompleted);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ACorePlayerController::ZoomTriggered);
	}
}

void ACorePlayerController::CameraPanTriggered(const FInputActionValue& InputActionValue)
{
	if (APawn* PossessedPawn = GetPawn())
	{
		const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
		const FRotator YawRotation = {0, GetControlRotation().Yaw, 0};
		const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);
		
		PossessedPawn->AddMovementInput(RotationMatrix.GetUnitAxis(EAxis::X), MovementVector.Y * CameraMovementSpeed);
		PossessedPawn->AddMovementInput(RotationMatrix.GetUnitAxis(EAxis::Y), MovementVector.X * CameraMovementSpeed);
	}
}

void ACorePlayerController::CameraRotateTriggered(const FInputActionValue& InputActionValue)
{
	const float RotationDirection = InputActionValue.Get<float>();

	if (APawn* PossessedPawn = GetPawn())
	{
		PossessedPawn->AddControllerYawInput(RotationDirection * CameraRotationSpeed);
	}
}

void ACorePlayerController::CommandCompleted()
{
	const IAbilitySystemInterface* SelectedActorAsi = Cast<IAbilitySystemInterface>(SelectedActor);
	if (!SelectedActorAsi) return;
	
	FHitResult HitResult;
	if (!GetHitResultUnderCursor(ECC_Visibility, false, HitResult)) return;

	if (!HitResult.GetActor()->Implements<USelectionInterface>())
	{
		FGameplayEventData GameplayEventData;
		GameplayEventData.TargetData.Add(new FGameplayAbilityTargetData_EndPont(HitResult.Location));
		SelectedActorAsi->GetAbilitySystemComponent()->HandleGameplayEvent(GTag_Ability_Move, &GameplayEventData);
	}
	else if (HitResult.GetActor()->IsA(AResourceBase::StaticClass()))
	{
		FGameplayEventData GameplayEventData;
		GameplayEventData.Target = HitResult.GetActor();
		SelectedActorAsi->GetAbilitySystemComponent()->HandleGameplayEvent(GTag_Ability_Gather, &GameplayEventData);
	}
}

void ACorePlayerController::SelectCompleted()
{
	FHitResult HitResult;
	if (!GetHitResultUnderCursor(ECC_Visibility, false, HitResult)) return;
	
	if (HitResult.GetActor()->Implements<USelectionInterface>())
	{
		SelectedActor = HitResult.GetActor();
	}
}

void ACorePlayerController::ZoomTriggered(const FInputActionValue& InputActionValue)
{
	const float ZoomDirection = InputActionValue.Get<float>();

	if (ACorePlayerControllerPawn* PossessedPawn = GetPawn<ACorePlayerControllerPawn>())
	{
		PossessedPawn->AddZoomInput(ZoomDirection);
	}
}

TWeakObjectPtr<AKarawan> ACorePlayerController::GetCurrentKarawan() const
{
	return CurrentKarawan;
}

TWeakObjectPtr<UGameplayHUDWidget> ACorePlayerController::GetGameplayHUDWidget() const
{
	if (UGameplayHUDWidget* GameplayHUDWidget = Cast<UGameplayHUDWidget>(HUD))
	{
		return GameplayHUDWidget;
	}
	return nullptr;
}
