// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceBase.h"

#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "Gameplay/Selection/SelectionComponent.h"

bool FResourceData::IsEmpty() const
{
	for (const TPair<EResourceType, int> Resource : Resources)
	{
		if (Resource.Value != 0) return false;
	}
	return true;
}

bool FResourceData::Contains(const FResourceTuple& ResourceTuple)
{
	return Resources.FindOrAdd(ResourceTuple.Type) >= ResourceTuple.Amount;
}

bool FResourceData::Contains(const TMap<EResourceType, int32>& ResourceMap)
{
	for (const auto& [ResourceType, Amount] : ResourceMap)
	{
		if (Resources.FindOrAdd(ResourceType) < Amount) return false;
	}
	
	return true;
}

void FResourceData::Add(const FResourceTuple& ResourceTuple)
{
	if (ResourceTuple.Amount <= 0) return;
	Resources.FindOrAdd(ResourceTuple.Type) += ResourceTuple.Amount;
	OnResourceChangedDelegate.Broadcast(ResourceTuple.Type, Resources[ResourceTuple.Type]);
}

void FResourceData::Add(const TMap<EResourceType, int32>& ResourceMap)
{
	for (const auto& [ResourceType, Amount] : ResourceMap)
	{
		Add({ResourceType, Amount});
	}
}

void FResourceData::Remove(const FResourceTuple& ResourceTuple)
{
	Resources[ResourceTuple.Type] -= FMath::Min(Resources.FindOrAdd(ResourceTuple.Type), ResourceTuple.Amount);
	OnResourceChangedDelegate.Broadcast(ResourceTuple.Type, Resources[ResourceTuple.Type]);
}

void FResourceData::Remove(const TMap<EResourceType, int32>& ResourceMap)
{
	for (const auto& [ResourceType, Amount] : ResourceMap)
	{
		Remove({ResourceType, Amount});
	}
}

bool FResourceData::TryRemove(const FResourceTuple& ResourceTuple)
{
	if (Resources.FindOrAdd(ResourceTuple.Type) < ResourceTuple.Amount) return false;
	Remove(ResourceTuple);
	return true;
}

bool FResourceData::TryRemove(const TMap<EResourceType, int32>& ResourceMap)
{
	for (const auto& [ResourceType, Amount] : ResourceMap)
	{
		if (Resources.FindOrAdd(ResourceType) < Amount) return false;
	}

	for (const auto& [ResourceType, Amount] : ResourceMap)
	{
		Remove({ResourceType, Amount});
	}

	return true;
}

void FResourceData::TransferTo(FResourceData& TargetResourceData, const FResourceTuple& ResourceTuple)
{
	FResourceTuple ResourceToTransfer;
	ResourceToTransfer.Type = ResourceTuple.Type;
	ResourceToTransfer.Amount = FMath::Min(Resources[ResourceTuple.Type], ResourceTuple.Amount);

	Remove(ResourceToTransfer);
	TargetResourceData.Add(ResourceToTransfer);
}

void FResourceData::MergeInto(FResourceData& TargetResourceData)
{
	for (auto& [ResourceType, ResourceAmount] : Resources)
	{
		TargetResourceData.Add({ResourceType, ResourceAmount});
		Remove({ResourceType, ResourceAmount});
	}
}

const TMap<EResourceType, int32>& FResourceData::Get() const
{
	return Resources;
}

EResourceType FResourceData::GetRandomAvailableResourceType() const
{
	if (Resources.Num() == 0) return EResourceType::Water;
	
	TArray<EResourceType> Keys;

	for (auto [Type, Amount] : Resources)
	{
		if (Amount > 0)
		{
			Keys.Add(Type);
		}
	} 

	return Keys[FMath::RandRange(0, Keys.Num() - 1)];
}

AResourceBase::AResourceBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->CanCharacterStepUpOn = ECB_No;
	RootComponent = SphereComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().NoCollision);
	StaticMeshComponent->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	SelectionComponent = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
}

UAbilitySystemComponent* AResourceBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USelectionComponent* AResourceBase::GetSelectionComponent() const
{
	return SelectionComponent;
}

FResourceData& AResourceBase::GetResourceData()
{
	return ResourceData;
}

int32 AResourceBase::GetAssignmentCapacity() const
{
	return AssignmentCapacity;
}
