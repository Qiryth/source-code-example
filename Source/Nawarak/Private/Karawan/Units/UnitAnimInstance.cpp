// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/Units/UnitAnimInstance.h"

#include "Karawan/Units/UnitBase.h"

void UUnitAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningUnit = Cast<AUnitBase>(TryGetPawnOwner());
}
