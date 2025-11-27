// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Units/UnitMovementComponent.h"

#include "Karawan/Units/UnitBase.h"

void UUnitMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);

	if (!MoveVelocity.IsNearlyZero())
	{
		PawnOwner->SetActorRotation(FMath::RInterpTo(PawnOwner->GetActorRotation(), MoveVelocity.Rotation(),
			GetWorld()->DeltaTimeSeconds,static_cast<AUnitBase*>(PawnOwner)->GetRotationSpeed()));	
	}
}
