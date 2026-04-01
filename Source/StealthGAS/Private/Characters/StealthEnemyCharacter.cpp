// Copyright Emil Almazov


#include "Characters/StealthEnemyCharacter.h"

#include "AIController.h"
#include "AbilitySystem/StealthAbilitySystemComponent.h"
#include "AbilitySystem/StealthAttributeSet.h"
#include "AI/SG_AIController.h"
#include "Components/StateTreeAIComponent.h"


AStealthEnemyCharacter::AStealthEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UStealthAbilitySystemComponent>("StealthAbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	
	// AI runs on server, not client, so AI data can't be replicated to other clients, therefore Minimal
	// Minimal in general is used for NPCs in multiplayer
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UStealthAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AStealthEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AStealthEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AStealthEnemyCharacter::HandleDeath()
{
	Super::HandleDeath();

	const auto* SG_AIController = GetController<ASG_AIController>();
	if (!IsValid(SG_AIController)) return;
	SG_AIController->GetStateTreeAI()->StopLogic(FString("Enemy is dead"));
}

void AStealthEnemyCharacter::HandleRespawn()
{
	Super::HandleRespawn();
	
	const auto* SG_AIController = GetController<ASG_AIController>();
	if (!IsValid(SG_AIController)) return;
	SG_AIController->GetStateTreeAI()->StartLogic();
}

void AStealthEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	if (!HasAuthority()) return;
	GiveStartupAbilities();
	InitializeAttributes();
	
	BindToHealthDelegate();
}

