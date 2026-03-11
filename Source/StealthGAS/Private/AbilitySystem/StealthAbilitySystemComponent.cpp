// Copyright Emil Almazov


#include "AbilitySystem/StealthAbilitySystemComponent.h"

#include "GameplayTags/StealthTags.h"


void UStealthAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	TryActivateAbilityIfTaggedOnGiven(AbilitySpec);
}

void UStealthAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	// Abilities might be given or removed during runtime so lock the abilities list so we dont accidentally activate a removed ability
	FScopedAbilityListLock ActiveScopeLock(*this);
	
	for (const auto& AbilitySpec : GetActivatableAbilities()) // list of all abilities GIVEN to this ACS
	{
		TryActivateAbilityIfTaggedOnGiven(AbilitySpec);
	}
}

void UStealthAbilitySystemComponent::SetAbilityLevel(const TSubclassOf<UGameplayAbility> Ability, const int32 Level)
{
	if (!IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;
	
	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(Ability))
	{
		AbilitySpec->Level = Level;
		MarkAbilitySpecDirty( *AbilitySpec);
	}
}

void UStealthAbilitySystemComponent::UpgradeAbilityLevel(const TSubclassOf<UGameplayAbility> Ability, const int32 Level)
{
	if (!IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;
	
	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(Ability))
	{
		AbilitySpec->Level += Level;
		MarkAbilitySpecDirty( *AbilitySpec);
	}
}

void UStealthAbilitySystemComponent::TryActivateAbilityIfTaggedOnGiven(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;
	
	if (AbilitySpec.Ability->GetAssetTags().HasTagExact(StealthTags::StealthAbilities::ActivateOnGiven))
	{
		TryActivateAbility(AbilitySpec.Handle);
	}
}
