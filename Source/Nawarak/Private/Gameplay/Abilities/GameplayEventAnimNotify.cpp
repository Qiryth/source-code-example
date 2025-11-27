// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Abilities/GameplayEventAnimNotify.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UGameplayEventAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner()))
	{
		const FGameplayEventData EventData;
		AbilitySystemInterface->GetAbilitySystemComponent()->HandleGameplayEvent(EventTag, &EventData);
	}
}
