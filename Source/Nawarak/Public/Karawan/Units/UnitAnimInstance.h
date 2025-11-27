// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UnitAnimInstance.generated.h"

class AUnitBase;
/**
 * 
 */
UCLASS()
class NAWARAK_API UUnitAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


// Lifecycle
public:
	virtual void NativeInitializeAnimation() override;


// Variables
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUnitBase> OwningUnit;
};
