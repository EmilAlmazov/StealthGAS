// Copyright Emil Almazov


#include "Player/StealthPlayerState.h"
#include "AbilitySystemComponent.h"

AStealthPlayerState::AStealthPlayerState()
{
	// see https://github.com/tranek/GASDocumentation?tab=readme-ov-file#41-ability-system-component
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AStealthPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
