// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AbilityTasks/AbilityTaskFunctionLibrary.h"

#include "Abilities/GameplayAbility.h"
#include "Core/GameInstance/BlueprintReferences.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "Karawan/Units/UnitBase.h"

bool UAbilityTaskFunctionLibrary::SpawnStackFromResource(UGameplayAbility* OwningAbility, AResourceBase* Resource, bool& Result)
{
	AUnitBase* OwningUnit = Cast<AUnitBase>(OwningAbility->GetOwningActorFromActorInfo());
	if (!OwningUnit || !Resource || Resource->GetResourceData().IsEmpty()) return Result;

	if (AResourceStack* ResourceStack = Resource->GetWorld()->SpawnActor<AResourceStack>(
		UCoreGameInstance::GetBlueprintReferences().Get_BP_ResourceStack()))
	{
		OwningUnit->GiveResourceStack(ResourceStack);
		Resource->GetResourceData().TransferTo(ResourceStack->GetResourceData(),
			{Resource->GetResourceData().GetRandomAvailableResourceType(), 1});

		Result = true;
	}
	
	return Result;
}

bool UAbilityTaskFunctionLibrary::DepositResourceStack(UGameplayAbility* OwningAbility, AKarawan* Karawan, bool& Result)
{
	AUnitBase* OwningUnit = Cast<AUnitBase>(OwningAbility->GetOwningActorFromActorInfo());
	if (!OwningUnit || !OwningUnit->HasResourceStack() || !Karawan) return Result;

	OwningUnit->TakeResourceStack()->GetResourceData().MergeInto(Karawan->GetResourceData());
	return Result = true;
}
