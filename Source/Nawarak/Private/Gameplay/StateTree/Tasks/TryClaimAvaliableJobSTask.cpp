// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/StateTree/Tasks/TryClaimAvaliableJobSTask.h"

#include "StateTreeExecutionContext.h"
#include "Karawan/JobBoard.h"
#include "Karawan/Units/UnitBase.h"


FTryClaimAvailableJobSTask::FTryClaimAvailableJobSTask()
{
	bShouldCallTick = true;
	bShouldCallTickOnlyOnEvents = false;
}

EStateTreeRunStatus FTryClaimAvailableJobSTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	auto& [Unit] = Context.GetInstanceData(*this);
	
	return Unit->GetKarawan()->GetJobBoard()->AssignUnitToJob(Unit) ? EStateTreeRunStatus::Succeeded :
		bRepeat ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus FTryClaimAvailableJobSTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	auto& [Unit] = Context.GetInstanceData(*this);
	
	return Unit->GetKarawan()->GetJobBoard()->AssignUnitToJob(Unit) ?
		EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Running;
}

#if WITH_EDITOR
FText FTryClaimAvailableJobSTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup,
	EStateTreeNodeFormatting Formatting) const
{
	return bRepeat ? FText::FromString("Try claim job <s>repeatedly</>") : FText::FromString("Try claim job <s>once</>");
}
#endif
