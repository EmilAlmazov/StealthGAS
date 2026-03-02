// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/StealthGameplayAbility.h"
#include "StealthHitReact.generated.h"


UCLASS()
class STEALTHGAS_API UStealthHitReact : public UStealthGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="StealthGAS|Abilities")
	void CalculateAndStoreDirections(const AActor* Instigator);
	
	
	UPROPERTY(BlueprintReadOnly, Category="StealthGAS|Abilities")
	FVector TargetForwardDirection;
	
	UPROPERTY(BlueprintReadOnly, Category="StealthGAS|Abilities")
	FVector TargetToInstigatorDirection;
};
