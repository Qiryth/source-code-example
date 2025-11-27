// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/Nodes/ResourceNode.h"

#include "Components/SphereComponent.h"
#include "Core/GameInstance/CoreGameInstance.h"
#include "Helpers/NavArea_Resource.h"

AResourceNode::AResourceNode()
{
	SphereComponent->SetCollisionProfileName(UCoreGameInstance::GetCollisionProfiles().ResourceNode);
	SphereComponent->bDynamicObstacle = true;
	SphereComponent->SetAreaClassOverride(UNavArea_Resource::StaticClass());

	AssignmentCapacity = 5;
}
