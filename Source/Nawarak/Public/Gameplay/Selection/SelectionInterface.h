// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInterface.generated.h"

class USelectionComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NAWARAK_API ISelectionInterface
{
	GENERATED_BODY()

public:
	virtual USelectionComponent* GetSelectionComponent() const = 0;	
};
