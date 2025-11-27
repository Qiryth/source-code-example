// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameInstance/CoreGameInstance.h"

#include "Core/GameInstance/BlueprintReferences.h"

TObjectPtr<UCoreGameInstance> UCoreGameInstance::Instance = nullptr;

FBlueprintReferences UCoreGameInstance::BlueprintReferences = FBlueprintReferences();
FCollisionProfiles UCoreGameInstance::CollisionProfiles = FCollisionProfiles();

FBlueprintReferences& UCoreGameInstance::GetBlueprintReferences()
{
	return BlueprintReferences;
}

const FCollisionProfiles& UCoreGameInstance::GetCollisionProfiles()
{
	return CollisionProfiles;
}

UCoreGameInstance::UCoreGameInstance()
{
	GetBlueprintReferences().Init();
}

void UCoreGameInstance::Init()
{
	Super::Init();

	if (Instance) return;
	Instance = this;
}

void UCoreGameInstance::Shutdown()
{
	Super::Shutdown();

	if (Instance != this) return;
	Instance = nullptr;
}
