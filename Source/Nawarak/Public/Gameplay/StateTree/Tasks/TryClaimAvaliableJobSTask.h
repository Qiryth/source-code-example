// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "TryClaimAvaliableJobSTask.generated.h"

class UJob;
class AUnitBase;

USTRUCT()
struct FTryClaimAvailableJobSTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AUnitBase> Unit;
};

/**
 * 
 */
USTRUCT(Category="Custom", DisplayName="Try Claim Available Job")
struct FTryClaimAvailableJobSTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FTryClaimAvailableJobSTaskInstanceData;

// Lifecycle
public:
	FTryClaimAvailableJobSTask();
	
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;


// Variables
	UPROPERTY(EditAnywhere)
	bool bRepeat = false;

	
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup,
		EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif
};
