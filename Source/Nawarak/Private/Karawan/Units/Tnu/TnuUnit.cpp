// Fill out your copyright notice in the Description page of Project Settings.

#include "Karawan/Units/Tnu/TnuUnit.h"

#include "Core/GameInstance/BlueprintReferences.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "Resources/Stacks/ResourceStack.h"

ATnuUnit::ATnuUnit()
{
	Abilities.Add(UCoreGameInstance::GetBlueprintReferences().Get_GA_Gather_Node());
}

bool ATnuUnit::HasResourceStack()
{
	return ResourceStack.IsValid();
}

void ATnuUnit::GiveResourceStack(TWeakObjectPtr<AResourceStack> NewResourceStack)
{
	Super::GiveResourceStack(NewResourceStack);

	if (NewResourceStack.IsValid())
	{
		if (ResourceStack.IsValid())
		{
			ResourceStack->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
		
		NewResourceStack->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		ResourceStack = NewResourceStack;
	}
}

TWeakObjectPtr<AResourceStack> ATnuUnit::TakeResourceStack()
{
	const TWeakObjectPtr<AResourceStack> ResourceStackToTake = ResourceStack;
	ResourceStack = nullptr;
	return ResourceStackToTake;
}
