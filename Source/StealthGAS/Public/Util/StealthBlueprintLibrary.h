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
	
	UFUNCTION(BlueprintCallable, Category = "StealthGAS|Abilities")
	static TArray<AActor*> HitBoxOverlapTest(AActor* AvatarActor, float HitBoxRadius, float HitBoxForwardOffset = 0.f, float HitBoxElevationOffset = 0.f, bool bIsDebugEnabled = false);
	
private:
	static void DrawHitBoxAndOverlaps(const UWorld* World, const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation, const float HitBoxRadius);
};
