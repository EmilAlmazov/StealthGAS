// Copyright Emil Almazov


#include "Characters/StealthBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/StealthAttributeSet.h"
#include "Net/UnrealNetwork.h"


AStealthBaseCharacter::AStealthBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void AStealthBaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bAlive);
}

void AStealthBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (const IGenericTeamAgentInterface* ControllerAsTeamProvider = Cast<IGenericTeamAgentInterface>(NewController))
	{
		TeamId = ControllerAsTeamProvider->GetGenericTeamId();
	}
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

void AStealthBaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect is not set"));
	ensure(GetAbilitySystemComponent());
	
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AStealthBaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0)
	{
		HandleDeath();
	}
}

void AStealthBaseCharacter::HandleDeath()
{
	bAlive = false;
	
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%s died"), *GetName()));
	}
}

void AStealthBaseCharacter::BindToHealthDelegate()
{
	const auto* SGAS_AttributeSet = Cast<UStealthAttributeSet>(GetAttributeSet());
	if (!IsValid(SGAS_AttributeSet)) return;
	const FGameplayAttribute HealthAttribute = SGAS_AttributeSet->GetHealthAttribute();
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(HealthAttribute).AddUObject( this, &ThisClass::OnHealthChanged);
}

void AStealthBaseCharacter::HandleRespawn()
{
	bAlive = true;
}

void AStealthBaseCharacter::ResetAttributes()
{
	checkf(IsValid(ResetAttributesEffect), TEXT("ResetAttributesEffect is not set"));
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(ResetAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

