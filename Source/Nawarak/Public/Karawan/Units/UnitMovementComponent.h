// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UnitMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class NAWARAK_API UUnitMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()


// Lifecycle
public:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
