// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/ResourceBase.h"
#include "ResourceStack.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NAWARAK_API AResourceStack : public AResourceBase
{
	GENERATED_BODY()


// Lifecycle
public:
	AResourceStack();
	
	virtual void BeginDestroy() override;


// Functions
private:
	void OnResourceChanged(EResourceType Resource, int I);
};
