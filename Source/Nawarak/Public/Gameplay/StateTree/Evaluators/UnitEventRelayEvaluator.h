// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "GameplayEffectTypes.h"
#include "Helpers/EnumCollection.h"
#include "UnitEventRelayEvaluator.generated.h"


class AUnitBase;

USTRUCT()
struct FUnitEventRelayEvaluatorInstanceData
{
	GENERATED_BODY()


// Variables
public:
	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AUnitBase> Unit;
	
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	FDelegateHandle RelayDelegateHandle;
	int LastCount = 0;
};

/**
 * 
 */
USTRUCT(Category="Custom", DisplayName="Unit Event Relay")
struct FUnitEventRelayEvaluator : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FUnitEventRelayEvaluatorInstanceData;

// Lifecycle
public:
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	
protected:
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	virtual void TreeStop(FStateTreeExecutionContext& Context) const override;


// Variables
public:
	UPROPERTY(EditAnywhere)
	EKarawanOrUnit ListenOn = EKarawanOrUnit::Karawan;
	UPROPERTY(EditAnywhere, meta=(Categories="_Ability,_State"))
	FGameplayTag ListenForTag;
	UPROPERTY(EditAnywhere, meta=(Categories="_Event"))
	FGameplayTag AddedTagEvent;
	UPROPERTY(EditAnywhere, meta=(Categories="_Event"))
	FGameplayTag RemovedTagEvent;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EGameplayTagEventType::Type> RelayCondition = EGameplayTagEventType::Type::NewOrRemoved;

	
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup,
		EStateTreeNodeFormatting Formatting) const override;
	virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& CompileContext) override;
#endif
};
