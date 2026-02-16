// Copyright Emil Almazov


#include "Characters/StealthBaseCharacter.h"


AStealthBaseCharacter::AStealthBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* AStealthBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

