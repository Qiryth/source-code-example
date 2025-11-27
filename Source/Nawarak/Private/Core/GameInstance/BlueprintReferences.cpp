// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameInstance/BlueprintReferences.h"


void FBlueprintReferences::Init()
{
#define BLUEPRINT_REFERENCE(Type, Name, PackagePath) Get_##Name();
	BLUEPRINT_REFERENCE_LIST
#undef BLUEPRINT_REFERENCE
}
