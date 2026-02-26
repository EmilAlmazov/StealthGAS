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
	TArray<AActor*> HitBoxOverlapTest();
	
	UFUNCTION(BlueprintCallable, Category = "StealthGAS|Abilities")
	void SendHitReactEventToEnemy(const TArray<AActor*>& ActorsHit);
	
private:
	void DrawHitBoxAndOverlaps(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS|Abilities")
	float HitBoxRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS|Abilities")
	float HitBoxForwardOffset = 200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS|Abilities")
	float HitBoxElevationOffset = 20.f;
};
