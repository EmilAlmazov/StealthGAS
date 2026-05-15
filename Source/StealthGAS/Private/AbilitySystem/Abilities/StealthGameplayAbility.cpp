// Copyright Emil Almazov

#include "AbilitySystem/Abilities/StealthGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Characters/StealthBaseCharacter.h"

static TAutoConsoleVariable CVarDebugAbilities(
	TEXT("Stealth.Debug.Abilities"),
	false,
	TEXT("Toggle debug drawing for gameplay abilities"),
	ECVF_Cheat
);


UStealthGameplayAbility::UStealthGameplayAbility()
{
	ActivationBlockedTags.AddTag(StealthTags::Status::Dead);
}

void UStealthGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (IsDebugEnabled() && IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("%s Activated: "), *GetName()));
	}
	
}

bool UStealthGameplayAbility::IsDebugEnabled()
{
	return CVarDebugAbilities.GetValueOnGameThread();
}

void UStealthGameplayAbility::ApplyDamageEffectToEnemy(const TArray<AActor*>& ActorsHit, TSubclassOf<UGameplayEffect> DamageEffect)
{
	if (!ensureMsgf(DamageEffect, TEXT("DamageEffect not assigned in %s"), *GetName())) return;
	
	UAbilitySystemComponent* ACS = GetAbilitySystemComponentFromActorInfo_Ensured();
	
	// Context Handle
	FGameplayEffectContextHandle ContextHandle = ACS->MakeEffectContext();
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	// Spec Handle
	const FGameplayEffectSpecHandle DamageEffectSpecHandle = ACS->MakeOutgoingSpec(DamageEffect, GetAbilityLevel(), ContextHandle);
	if (!DamageEffectSpecHandle.IsValid()) return;
	
	for (auto& Actor : ActorsHit)
	{
		if (!IsValid(Actor)) continue;
		
		UAbilitySystemComponent* ActorACS = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
		if (ActorACS)
		{
			ACS->ApplyGameplayEffectSpecToTarget(*DamageEffectSpecHandle.Data.Get(), ActorACS);
		}
	}
}
