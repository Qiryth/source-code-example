// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilityTaskFunctionLibrary.generated.h"

class AKarawan;
class AResourceBase;
class UGameplayAbility;

/**
 * 
 */
UCLASS()
class NAWARAK_API UAbilityTaskFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


// Static
public:
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", ExpandEnumAsExecs="Result"))
	static bool SpawnStackFromResource(UGameplayAbility* OwningAbility, AResourceBase* Resource, bool& Result);
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", ExpandEnumAsExecs="Result"))
	static bool DepositResourceStack(UGameplayAbility* OwningAbility, AKarawan* Karawan, bool& Result);
};
