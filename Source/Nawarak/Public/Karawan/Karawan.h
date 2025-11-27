// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Gameplay/Selection/FactionObject.h"
#include "Resources/ResourceBase.h"
#include "Karawan.generated.h"

class UJobBoard;
class AUnitBase;
class AResourceBase;
class USphereComponent;

USTRUCT()
struct FKarawanData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FLimitedResourceData ResourceData;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AUnitBase> LeadUnit;
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<AUnitBase>, int> Units;
	UPROPERTY(EditAnywhere)
	EFaction Faction = EFaction::None;
};

UCLASS(meta=(PrioritizeCategories="Custom"))
class NAWARAK_API AKarawan : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()


// Lifecycle
public:
	AKarawan();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


// Functions
public:
	void RegisterUnit(TWeakObjectPtr<AUnitBase> Unit);
	void UnregisterUnit(TWeakObjectPtr<AUnitBase> Unit);
	void RegisterLeadUnit(TWeakObjectPtr<AUnitBase> Unit);

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


// Accessors
public:
	UFUNCTION(BlueprintPure)
	TArray<AUnitBase*> GetUnitsWithBuildingSlots();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	TWeakObjectPtr<UJobBoard> GetJobBoard();
	TWeakObjectPtr<AUnitBase> GetLeadUnit() const;
	FResourceData& GetResourceData();	

protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AUnitBase> LeadUnit;
	
// Variables
private:
	UPROPERTY(Transient)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UJobBoard> JobBoard;

	UPROPERTY(EditAnywhere, Category="Custom")
	FKarawanData KarawanData;

	TArray<TWeakObjectPtr<AUnitBase>> Units;
	TArray<TWeakObjectPtr<AResourceBase>> ResourcesInRange;
};
