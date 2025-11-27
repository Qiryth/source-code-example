// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/Selection/SelectionInterface.h"
#include "BuildingBase.generated.h"


struct FResourceTuple;
enum class EResourceType : uint8;
class AUnitBase;
class UBuildingActiveBase;
class UBuildingPassiveBase;

UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API ABuildingBase : public AActor, public ISelectionInterface
{
	GENERATED_BODY()

	friend class UBuildingActiveBase;
	// friend class UBuildingSelectionWidget;

	
// Lifecycle
public:	
	ABuildingBase();


// Functions
	void Init();

	
// Accessors
public:
	UFUNCTION(BlueprintCallable)
	virtual USelectionComponent* GetSelectionComponent() const override;
	TWeakObjectPtr<UTexture2D> GetBuildingIcon() const;
	const FText& GetDescription() const;
	const TMap<EResourceType, int32>& GetConstructionCost() const;

	TWeakObjectPtr<AUnitBase> GetOwningUnit() const;

// Variables
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TObjectPtr<UTexture2D> BuildingIcon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom")
	TMap<EResourceType, int32> ConstructionCost;
	
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category="Custom")
	TArray<TObjectPtr<UBuildingPassiveBase>> BuildingPassives;
	
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category="Custom")
	TArray<TObjectPtr<UBuildingActiveBase>> BuildingActives;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UBuildingActiveBase>> BuildingActiveQueue;
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UBuildingActiveBase> CurrentBuildingActive;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USelectionComponent> SelectionComponent;	
};
