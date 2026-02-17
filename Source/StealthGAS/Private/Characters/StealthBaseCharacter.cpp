// Copyright Emil Almazov


#include "Characters/StealthBaseCharacter.h"

#include "AbilitySystemComponent.h"


AStealthBaseCharacter::AStealthBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* AStealthBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AStealthBaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec GameplayAbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(GameplayAbilitySpec);
	}
}

