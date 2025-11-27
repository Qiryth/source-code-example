// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/StateTree/Evaluators/UnitEventRelayEvaluator.h"

#include "AbilitySystemComponent.h"
#include "Helpers/EnumCollection.h"
#include "StateTreeExecutionContext.h"
#include "Karawan/Units/UnitBase.h"


void FUnitEventRelayEvaluator::TreeStart(FStateTreeExecutionContext& Context) const
{
	Super::TreeStart(Context);
	
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	InstanceData.AbilitySystemComponent = ListenOn == EKarawanOrUnit::Karawan ?
		InstanceData.Unit->GetKarawan()->GetAbilitySystemComponent() :
		InstanceData.Unit->GetAbilitySystemComponent();

	FStateTreeWeakExecutionContext WeakContext = Context.MakeWeakExecutionContext();

	InstanceData.RelayDelegateHandle = InstanceData.AbilitySystemComponent->RegisterGameplayTagEvent(ListenForTag, RelayCondition).AddLambda(
		[this, WeakContext](FGameplayTag Tag, const int Count)
	{
		FInstanceDataType* InstanceDataPtr = WeakContext.MakeStrongExecutionContext().GetInstanceDataPtr<FInstanceDataType>();
			
		const FGameplayTag EventTag = Count > InstanceDataPtr->LastCount ? AddedTagEvent : RemovedTagEvent;
		InstanceDataPtr->LastCount = Count;

		if (!EventTag.IsValid()) return;

		if (!WeakContext.SendEvent(EventTag))
		{
			UE_LOG(LogScript, Error, TEXT("[RelayDelegate] Could not send event with tag: %s"), *EventTag.GetTagName().ToString());
		}
	});
}

void FUnitEventRelayEvaluator::TreeStop(FStateTreeExecutionContext& Context) const
{
	Super::TreeStop(Context);

	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (!InstanceData.AbilitySystemComponent.IsValid()) return;

	InstanceData.AbilitySystemComponent->UnregisterGameplayTagEvent(InstanceData.RelayDelegateHandle, ListenForTag, RelayCondition);
}


#if WITH_EDITOR
FText FUnitEventRelayEvaluator::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup,
												   EStateTreeNodeFormatting Formatting) const
{
	return FText::Format(FText::FromString("Listen for <s>{0}</> {1} <s>on</> {2}"),
		RelayCondition == EGameplayTagEventType::NewOrRemoved ?
			FText::FromString("New or Removed") :
			FText::FromString("Any Count Change"),
		FText::FromString(ListenForTag.ToString()),
		FText::FromString(StaticEnum<EKarawanOrUnit>()->GetNameStringByValue(static_cast<int64>(ListenOn))));
}

EDataValidationResult FUnitEventRelayEvaluator::Compile(UE::StateTree::ICompileNodeContext& CompileContext)
{
	EDataValidationResult DataValidationResult = EDataValidationResult::Valid;
	
	if (!ListenForTag.IsValid())
	{
		CompileContext.AddValidationError(FText::FromString("Listen for Tag is empty"));
		DataValidationResult = EDataValidationResult::Invalid;
	}

	if (!AddedTagEvent.IsValid() && !RemovedTagEvent.IsValid())
	{
		CompileContext.AddValidationError(FText::FromString("At least one Tag Event is needed"));
		DataValidationResult = EDataValidationResult::Invalid;
	}
	
	return DataValidationResult;
}
#endif
