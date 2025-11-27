// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/Stacks/ResourceStack.h"

#include "Components/SphereComponent.h"
#include "Core/GameInstance/CoreGameInstance.h"

AResourceStack::AResourceStack()
{
	SphereComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().ResourceStack);
	ResourceData.OnResourceChangedDelegate.AddUObject(this, &AResourceStack::OnResourceChanged);
}

void AResourceStack::BeginDestroy()
{
	Super::BeginDestroy();

	ResourceData.OnResourceChangedDelegate.RemoveAll(this);
}

void AResourceStack::OnResourceChanged(EResourceType Resource, int I)
{
	if (ResourceData.IsEmpty()) Destroy();
}
