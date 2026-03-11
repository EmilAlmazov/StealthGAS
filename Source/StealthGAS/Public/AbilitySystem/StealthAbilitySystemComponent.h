// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "StealthAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEALTHGAS_API UStealthAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	// Activate ability as soon as it is given
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	
	// Activate ability on clients too
	void virtual OnRep_ActivateAbilities() override;
	
	UFUNCTION(BlueprintCallable, Category = "StealthGAS|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> Ability, int32 Level);
	
	UFUNCTION(BlueprintCallable, Category = "StealthGAS|Abilities")
	void UpgradeAbilityLevel(TSubclassOf<UGameplayAbility> Ability, int32 Level = 1);
	
private:
	void TryActivateAbilityIfTaggedOnGiven(const FGameplayAbilitySpec& AbilitySpec);
	
	
};
