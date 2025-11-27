// Fill out your copyright notice in the Description page of Project Settings.


#include "Karawan/JobBoard.h"

#include "AbilitySystemComponent.h"
#include "Algo/RandomShuffle.h"
#include "Gameplay/GameplayTagDeclarations.h"
#include "Karawan/Karawan.h"
#include "Karawan/Units/UnitBase.h"
#include "Resources/ResourceBase.h"

FJob FJob::CreateGatherJob(const TWeakObjectPtr<AResourceBase> ResourceBase)
{
	FJob NewJob = FJob(GTag_Ability_Gather, ResourceBase, ResourceBase->GetAssignmentCapacity());
	NewJob.AssignementConditionsPredicate = [ResourceBase]()
	{
		return ResourceBase.IsValid() && !ResourceBase->GetResourceData().IsEmpty() && ResourceBase->GetAttachParentActor() == nullptr;
	};
	return NewJob;
}

bool FJob::CanBeAssigned() const
{
	return !IsFullyAssigned() && AssignementConditionsPredicate.IsSet() && AssignementConditionsPredicate();
}

UJobBoard::UJobBoard()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UJobBoard::BeginPlay()
{
	Super::BeginPlay();

	OwningKarawan = Cast<AKarawan>(GetOwner());
	if (!OwningKarawan.IsValid()) return;

	OwningKarawan->OnActorBeginOverlap.AddDynamic(this, &UJobBoard::OnActorBeginOverlap);
	OwningKarawan->OnActorEndOverlap.AddDynamic(this, &UJobBoard::OnActorEndOverlap);
}

bool UJobBoard::AssignUnitToJob(TWeakObjectPtr<AUnitBase> Unit)
{
	TArray<FJob> PossibleJobs = Jobs.FilterByPredicate([&Unit](const FJob& Job)
	{
		return Unit->HasAbilityWithTag(Job.AbilityTag) && Job.CanBeAssigned();
	});

	if (PossibleJobs.Num() == 0) return false;

	// TODO: Here would be weightened decision
	Algo::RandomShuffle(PossibleJobs);

	FJob& SelectedJob = Jobs[Jobs.Find(PossibleJobs[0])];
	
	FGameplayEventData GameplayEventData;
	GameplayEventData.EventTag = SelectedJob.AbilityTag;
	GameplayEventData.Target = SelectedJob.TargetActor.Get();
	Unit->GetAbilitySystemComponent()->HandleGameplayEvent(SelectedJob.AbilityTag, &GameplayEventData);
	
	SelectedJob.AssignedUnits.Add(Unit);
	if (SelectedJob.IsFullyAssigned())
	{
		OwningKarawan->GetAbilitySystemComponent()->RemoveLooseGameplayTag(GTag_State_Has_Job);
	}

	return true;
}

void UJobBoard::InformJobCompleted(TWeakObjectPtr<AUnitBase> Unit)
{
	FJob* AssignedJob = Jobs.FindByPredicate([Unit](const FJob& Job)
	{
		return Job.AssignedUnits.Contains(Unit);
	});

	if (AssignedJob == nullptr) return;
	
	if (AssignedJob->IsFullyAssigned())
	{
		OwningKarawan->GetAbilitySystemComponent()->AddLooseGameplayTag(GTag_State_Has_Job);
	}
	AssignedJob->AssignedUnits.Remove(Unit);
}

void UJobBoard::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (AResourceBase* OtherResource = Cast<AResourceBase>(OtherActor))
	{
		if (ListJobsForTheseAbilityTags.HasTag(GTag_Ability_Gather))
		{
			Jobs.Add(FJob::CreateGatherJob(OtherResource));
			OwningKarawan->GetAbilitySystemComponent()->AddLooseGameplayTag(GTag_State_Has_Job);
		}
	}
}

void UJobBoard::OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Jobs.RemoveAll([this, OtherActor](const FJob& Job)
	{
		if (Job.TargetActor != OtherActor) return false;

		if (!Job.IsFullyAssigned())
		{
			OwningKarawan->GetAbilitySystemComponent()->RemoveLooseGameplayTag(GTag_State_Has_Job);
		}
		
		return true;
	});
}
