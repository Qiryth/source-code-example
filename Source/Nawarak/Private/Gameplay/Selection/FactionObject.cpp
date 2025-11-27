// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Selection/FactionObject.h"

void UFactionObject::RegisterKarawan(const TWeakObjectPtr<AKarawan> Karawan)
{
	Karawans.Add(Karawan);
}

TWeakObjectPtr<AKarawan> UFactionObject::GetNextKarawan()
{
	if (Karawans.Num() == 0) return nullptr;

	CurrentKarawanIndex = (CurrentKarawanIndex + 1) % Karawans.Num();
	return Karawans[CurrentKarawanIndex];
}
