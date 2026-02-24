// Copyright Emil Almazov

#include "AbilitySystem/Abilities/StealthGameplayAbility.h"

static TAutoConsoleVariable CVarDebugAbilities(
	TEXT("Stealth.Debug.Abilities"),
	false,
	TEXT("Toggle debug drawing for gameplay abilities"),
	ECVF_Cheat
);

void UStealthGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bShouldDebug = CVarDebugAbilities.GetValueOnGameThread();
	UE_CLOG(bShouldDebug, LogTemp, Warning, TEXT("Ability Activated: %s"), *GetName());
}

bool UStealthGameplayAbility::IsDebugEnabled()
{
	return CVarDebugAbilities.GetValueOnGameThread();
}
