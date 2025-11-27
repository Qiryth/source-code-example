// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Resources/Stacks/ResourceStack.h"
#include "BlueprintReferences.generated.h"


#define BLUEPRINT_REFERENCE_LIST \
BLUEPRINT_REFERENCE(UGameplayAbility, GA_Move, "/Game/Gameplay/Abilities/GA_Move") \
BLUEPRINT_REFERENCE(UGameplayAbility, GA_Gather_Node, "/Game/Gameplay/Abilities/GA_Gather_Node") \
BLUEPRINT_REFERENCE(AResourceStack, BP_ResourceStack, "/Game/Resources/Stacks/BP_ResourceStack") \
BLUEPRINT_REFERENCE(UUserWidget, WBP_GameplayHUD, "/Game/UI/Gameplay/WBP_GameplayHUD") \


#define CREATE_BLUEPRINT_REFERENCE(Type, Name, PackagePath) \
private: \
	TSubclassOf<Type> Name; \
public: \
	TSubclassOf<Type> Get_##Name() \
	{ \
		if (!Name) { \
			static ConstructorHelpers::FClassFinder<Type> FoundClass(TEXT(PackagePath)); \
			if (FoundClass.Succeeded()) \
			{ \
				Name = FoundClass.Class; \
			} \
			else \
			{ \
				UE_LOG(LogScript, Error, TEXT("Blueprint Reference not valid: %s"), TEXT(PackagePath)); \
			} \
		} \
		return Name; \
	} \


/**
 * 
 */
USTRUCT()
struct NAWARAK_API FBlueprintReferences
{
	GENERATED_BODY()

	friend class UCoreGameInstance;
	
private:
	void Init();
	
#define BLUEPRINT_REFERENCE(Type, Name, PackagePath) CREATE_BLUEPRINT_REFERENCE(Type, Name, PackagePath)
	BLUEPRINT_REFERENCE_LIST
#undef BLUEPRINT_REFERENCE
};
