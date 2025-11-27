// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CoreGameInstance.generated.h"

struct FBlueprintReferences;

USTRUCT()
struct FCollisionProfiles
{
	GENERATED_BODY()
	
// Variables
public:
	FName NoCollision = FName(TEXT("NoCollision"));
	FName Karawan = FName(TEXT("_Karawan"));
	FName Krubb = FName(TEXT("_Krubb"));
	FName ResourceNode = FName(TEXT("_ResourceNode"));
	FName ResourceStack = FName(TEXT("_ResourceStack"));
	FName Unit = FName(TEXT("_Unit"));
	FName Unit_Walking = FName(TEXT("_Unit_Walking"));
};


/**
 * 
 */
UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API UCoreGameInstance : public UGameInstance
{
	GENERATED_BODY()

	
// Static
public:
	static FBlueprintReferences& GetBlueprintReferences();
	static const FCollisionProfiles& GetCollisionProfiles();
	
private:
	static TObjectPtr<UCoreGameInstance> Instance;
	static FBlueprintReferences BlueprintReferences;
	static FCollisionProfiles CollisionProfiles;
	
// Lifecycle
public:
	UCoreGameInstance();
	
	virtual void Init() override;
	virtual void Shutdown() override;
};
