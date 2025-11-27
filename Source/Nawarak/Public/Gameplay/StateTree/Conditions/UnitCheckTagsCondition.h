// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "Helpers/EnumCollection.h"
#include "UnitCheckTagsCondition.generated.h"

class AUnitBase;

USTRUCT()
struct FUnitCheckTagsConditionInstanceData
{
	GENERATED_BODY()


// Variables
public:
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AUnitBase> Unit;
};

/**
 * 
 */
USTRUCT(Category="Custom", DisplayName="Unit Check Tags")
struct FUnitCheckTagsCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FUnitCheckTagsConditionInstanceData;

	
// Lifecycle
public:
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;


// Variables
public:
	UPROPERTY(EditAnywhere)
	EKarawanOrUnit CheckOn = EKarawanOrUnit::Karawan;
	UPROPERTY(EditAnywhere, meta=(Categories="_Ability,_State"))
	FGameplayTagContainer CheckForTags;
	UPROPERTY(EditAnywhere)
	EGameplayContainerMatchType MatchType = EGameplayContainerMatchType::All;
	UPROPERTY(EditAnywhere)
	bool Invert = false;


#if WITH_EDITOR
public:
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup,
		EStateTreeNodeFormatting Formatting) const override;
	virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& CompileContext) override;
#endif
};
