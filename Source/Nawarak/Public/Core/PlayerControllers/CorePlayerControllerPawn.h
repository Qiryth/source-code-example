// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CorePlayerControllerPawn.generated.h"

class UFloatingPawnMovement;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API ACorePlayerControllerPawn : public APawn
{
	GENERATED_BODY()


// Lifecycle
public:
	ACorePlayerControllerPawn();
	

// Functions
public:
	void AddZoomInput(const float Value) const;

	
// Variables
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
};
