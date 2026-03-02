// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StealthBlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Forward,
	Back
};

UCLASS()
class STEALTHGAS_API UStealthBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static EHitDirection GetHitDirection(const FVector& TargetForwardDirection, const FVector& TargetToInstigatorDirection);
	
	UFUNCTION(BlueprintPure)
	static FName GetHitDirectionName(EHitDirection HitDirection);
};
