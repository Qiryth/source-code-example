// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/StateTree/Conditions/UnitCheckTagsCondition.h"

#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"
#include "Karawan/Units/UnitBase.h"


bool FUnitCheckTagsCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	auto& [Unit] = Context.GetInstanceData(*this);

	const UAbilitySystemComponent* AbilitySystemComponent = CheckOn == EKarawanOrUnit::Karawan ?
		Unit->GetKarawan()->GetAbilitySystemComponent() :
		Unit->GetAbilitySystemComponent();

	const bool Result = MatchType == EGameplayContainerMatchType::All ?
		AbilitySystemComponent->HasAllMatchingGameplayTags(CheckForTags) :
		AbilitySystemComponent->HasAnyMatchingGameplayTags(CheckForTags);
	
	return Result != Invert;
}

#if WITH_EDITOR
FText FUnitCheckTagsCondition::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup,
											EStateTreeNodeFormatting Formatting) const
{
	if (CheckForTags.IsEmpty())
	{
		return MatchType == EGameplayContainerMatchType::All != Invert ?
			FText::FromString("true <s>(empty gameplay tag container)</>") :
			FText::FromString("false <s>(empty gameplay tag container)</>");
	}
	
	return FText::Format(FText::FromString("{0} <s>{1}{2}</> {3}"),
	FText::FromString(StaticEnum<EKarawanOrUnit>()->GetNameStringByValue(static_cast<int64>(CheckOn))),
	Invert ?
		FText::FromString("lacks") :
		FText::FromString("contains"),
	CheckForTags.Num() <= 1 ?
		FText::FromString("") :
		MatchType == EGameplayContainerMatchType::All ?
			FText::FromString(" All") :
			FText::FromString(" Any"),
	CheckForTags.Num() != 0 ?
		FText::FromString(CheckForTags.ToStringSimple()) :
		FText::FromString("None"));
}

EDataValidationResult FUnitCheckTagsCondition::Compile(UE::StateTree::ICompileNodeContext& CompileContext)
{
	EDataValidationResult DataValidationResult = EDataValidationResult::Valid;
	
	if (CheckForTags.IsEmpty())
	{
		CompileContext.AddValidationError(FText::FromString("Check for Tags is empty"));
		DataValidationResult = EDataValidationResult::Invalid;
	}

	return DataValidationResult;
}
#endif
