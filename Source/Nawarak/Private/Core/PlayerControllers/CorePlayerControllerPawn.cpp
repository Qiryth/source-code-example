// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerControllers/CorePlayerControllerPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

ACorePlayerControllerPawn::ACorePlayerControllerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->TargetArmLength = 2000.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	RootComponent = SpringArmComponent;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawnMovement->bAutoRegisterUpdatedComponent = true;
}

void ACorePlayerControllerPawn::AddZoomInput(const float Value) const
{
	SpringArmComponent->TargetArmLength += Value;
}
