// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "KarawanWidgetBase.generated.h"

class ACorePlayerController;
class AKarawan;

/**
 * 
 */
UCLASS(Abstract, meta=(PrioritizeCategories="Custom"))
class NAWARAK_API UKarawanWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()
	
	
// Lifecycle
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


// Functions
protected:
	virtual void PreKarawanChanged() {};
	virtual void PostKarawanChanged() {};
	
	UFUNCTION(BlueprintImplementableEvent)
	void KarawanChanged();

	
// Accessors
public:
	void SetKarawan(TWeakObjectPtr<AKarawan> Karawan);
	

// Variables
protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AKarawan> TrackedKarawan;
	
private:
	TWeakObjectPtr<ACorePlayerController> OwningCorePlayerController;
};
