// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/StealthGameplayAbility.h"
#include "StealthPrimary.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAS_API UStealthPrimary : public UStealthGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "StealthGAS|Abilities")
	void SendHitReactEventToEnemy(const TArray<AActor*>& ActorsHit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StealthGAS|Abilities")
	float HitBoxRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StealthGAS|Abilities")
	float HitBoxForwardOffset = 200.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StealthGAS|Abilities")
	float HitBoxElevationOffset = 20.f;
};
