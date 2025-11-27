// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Gameplay/Selection/SelectionInterface.h"
#include "ResourceBase.generated.h"

class AResourceStack;
class USphereComponent;
enum class EResourceType : uint8;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnResourceChangedDelegate, EResourceType, int32)

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Water,
	Bone,
	Kelp,
	CarvedBone,
	Rope,
};


USTRUCT(BlueprintType)
struct FResourceTuple
{
	GENERATED_BODY()
	
	
// Lifecycle
	FResourceTuple() {};
	FResourceTuple(const EResourceType Type, const int32 Amount): Type(Type), Amount(Amount) {}


// Variables
	UPROPERTY(EditAnywhere)
	EResourceType Type = EResourceType::Water;
	UPROPERTY(EditAnywhere)
	int32 Amount = 0;
};


USTRUCT()
struct FResourceData
{
	GENERATED_BODY()

	
// Functions
public:
	bool IsEmpty() const;
	bool Contains(const FResourceTuple& ResourceTuple);
	bool Contains(const TMap<EResourceType, int32>& ResourceMap);
	void Add(const FResourceTuple& ResourceTuple);
	void Add(const TMap<EResourceType, int32>& ResourceMap);
	void Remove(const FResourceTuple& ResourceTuple);
	void Remove(const TMap<EResourceType, int32>& ResourceMap);
	bool TryRemove(const FResourceTuple& ResourceTuple);
	bool TryRemove(const TMap<EResourceType, int32>& ResourceMap);
	void TransferTo(FResourceData& TargetResourceData, const FResourceTuple&);
	void MergeInto(FResourceData& TargetResourceData);


// Accessors
public:
	const TMap<EResourceType, int32>& Get() const;
	EResourceType GetRandomAvailableResourceType() const;
	bool TryGetRandomResourceType(EResourceType& OutResourceType);
	FOnResourceChangedDelegate OnResourceChangedDelegate;

	
// Variables
private:
	UPROPERTY(EditAnywhere)
	TMap<EResourceType, int32> Resources;
};

USTRUCT()
struct FLimitedResourceData : public FResourceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 ResourceBaseLimits = 0;
	UPROPERTY(Transient)
	TMap<EResourceType, int32> ResourceLimitIncreases;
};


UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API AResourceBase : public AActor, public IAbilitySystemInterface, public ISelectionInterface
{
	GENERATED_BODY()


// Lifecycle
public:	
	AResourceBase();


// Accessors
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual USelectionComponent* GetSelectionComponent() const override;
	FResourceData& GetResourceData();
	int32 GetAssignmentCapacity() const;


// Variables
protected:
	UPROPERTY(Transient)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(Transient)
	TObjectPtr<USelectionComponent> SelectionComponent;

	UPROPERTY(EditAnywhere, Category="Custom")
	FResourceData ResourceData;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	int32 AssignmentCapacity = 1;
};
