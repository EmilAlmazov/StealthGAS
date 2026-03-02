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

	if (IsDebugEnabled() && IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("%s Activated: "), *GetName()));
	}
	
}

bool UStealthGameplayAbility::IsDebugEnabled()
{
	return CVarDebugAbilities.GetValueOnGameThread();
}
