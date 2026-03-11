// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "StealthGameplayAbility.generated.h"

UCLASS()
class STEALTHGAS_API UStealthGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stealth|Debug")
	static bool IsDebugEnabled();

	UFUNCTION(BlueprintCallable, Category = "StealthGAS|Abilities")
	void ApplyDamageEffectToEnemy(const TArray<AActor*>& ActorsHit, TSubclassOf<UGameplayEffect> DamageEffect);
};
