// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameStates/CoreGameState.h"

#include "Gameplay/Selection/FactionObject.h"

TWeakObjectPtr<UFactionObject> ACoreGameState::GetFactionObject(const EFaction Faction)
{
	if (!FactionObjects.Contains(Faction))
	{
		UFactionObject* FactionObject = NewObject<UFactionObject>();
		FactionObjects.Add({Faction, TStrongObjectPtr<UFactionObject>(FactionObject)});
	}
	
	return FactionObjects[Faction].Get();
}
