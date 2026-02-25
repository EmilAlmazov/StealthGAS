// Copyright Emil Almazov


#include "Characters/StealthEnemyCharacter.h"
#include "AbilitySystem/StealthAbilitySystemComponent.h"


AStealthEnemyCharacter::AStealthEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UStealthAbilitySystemComponent>("StealthAbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	
	// AI runs
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* AStealthEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AStealthEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	
	if (!HasAuthority()) return;
	GiveStartupAbilities();
	
}

