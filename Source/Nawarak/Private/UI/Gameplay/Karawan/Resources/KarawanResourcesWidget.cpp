// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Gameplay/Karawan/Resources/KarawanResourcesWidget.h"

#include "Karawan/Karawan.h"

void UKarawanResourcesWidget::PreKarawanChanged()
{
	if (TrackedKarawan.IsValid())
	{
		TrackedKarawan->GetResourceData().OnResourceChangedDelegate.RemoveAll(this);
	}
}

void UKarawanResourcesWidget::PostKarawanChanged()
{
	TrackedKarawan->GetResourceData().OnResourceChangedDelegate.AddUObject(this, &UKarawanResourcesWidget::ResourceChanged);
	for (const auto& [ResourceType, ResourceCount] : TrackedKarawan->GetResourceData().Get())
	{
		ResourceChanged(ResourceType, ResourceCount);
	}
}
