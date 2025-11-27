// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Gameplay/GameplayTagDeclarations.h"
#include "GameplayEventAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class NAWARAK_API UGameplayEventAnimNotify : public UAnimNotify
{
public:

private:
	GENERATED_BODY()


// Lifecycle
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


// Variables
private:
	UPROPERTY(EditAnywhere, Category="Custom", meta=(Categories="_Event.AnimNotify"))
	FGameplayTag EventTag = GTag_Event_AnimNotify;
};
