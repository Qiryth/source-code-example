// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "CorePlayerController.generated.h"

class UGameplayHUDWidget;
class UFactionObject;
class AKarawan;
class ISelectionInterface;
class UAbilitySystemComponent;
class ACorePlayerControllerPawn;
class UInputAction;
class UInputMappingContext;

// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKarawanChangedDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FKarawanChangedDelegate, TWeakObjectPtr<AKarawan>)

/**
 * 
 */
UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API ACorePlayerController : public APlayerController
{
	GENERATED_BODY()

	
// Lifecycle
public:
	ACorePlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


// Functions
protected:
	void CameraPanTriggered(const FInputActionValue& InputActionValue);
	void CameraRotateTriggered(const FInputActionValue& InputActionValue);
	void CommandCompleted();
	void SelectCompleted();
	void ZoomTriggered(const FInputActionValue& InputActionValue);


// Accessors
public:
	TWeakObjectPtr<AKarawan> GetCurrentKarawan() const;
	TWeakObjectPtr<UGameplayHUDWidget> GetGameplayHUDWidget() const;
	
	
// Variables
public:
	FKarawanChangedDelegate KarawanChangedDelegate;

private:
	// Camera
	UPROPERTY(EditDefaultsOnly, Category="Custom|Camera")
	float CameraBasePitch = 55.f;
	UPROPERTY(EditDefaultsOnly, Category="Custom|Camera")
	float CameraRotationSpeed = 1.f;
	UPROPERTY(EditDefaultsOnly, Category="Custom|Camera")
	float CameraMovementSpeed = 1.f;
	UPROPERTY(EditDefaultsOnly, Category="Custom|Camera")
	float CameraZoomSpeed = 1.f;


	// Inputs
	UPROPERTY(EditDefaultsOnly, Category="Custom|Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Input")
	TObjectPtr<UInputAction> CameraPanAction;
	UPROPERTY(EditDefaultsOnly, Category="Custom|Input")
	TObjectPtr<UInputAction> CameraRotateAction;
	UPROPERTY(EditDefaultsOnly, Category="Custom|Input")
	TObjectPtr<UInputAction> CommandAction;
	UPROPERTY(EditDefaultsOnly, Category="Custom|Input")
	TObjectPtr<UInputAction> SelectAction;
	UPROPERTY(EditDefaultsOnly, Category="Custom|Input")
	TObjectPtr<UInputAction> ZoomAction;

	TWeakObjectPtr<UFactionObject> CurrentFactionObject;
	TWeakObjectPtr<AKarawan> CurrentKarawan;
	TWeakObjectPtr<AActor> SelectedActor;
	TWeakObjectPtr<UUserWidget> HUD;
};
