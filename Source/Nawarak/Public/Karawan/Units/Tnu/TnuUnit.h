// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Karawan/Units/UnitBase.h"
#include "TnuUnit.generated.h"

class AResourceStack;

/**
 * 
 */
UCLASS(Abstract)
class NAWARAK_API ATnuUnit : public AUnitBase
{
	GENERATED_BODY()


// Lifecycle
public:
	ATnuUnit();

	virtual bool HasResourceStack() override;
	virtual void GiveResourceStack(TWeakObjectPtr<AResourceStack> NewResourceStack) override;
	virtual TWeakObjectPtr<AResourceStack> TakeResourceStack() override;


// Variables
private:
	TWeakObjectPtr<AResourceStack> ResourceStack;
};
