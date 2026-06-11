// Copyright Emil Almazov


#include "Util/StealthBlueprintLibrary.h"

#include "Characters/StealthCharacter.h"
#include "Engine/OverlapResult.h"

EHitDirection UStealthBlueprintLibrary::GetHitDirection(const FVector& TargetForwardDirection, const FVector& TargetToInstigatorDirection)
{
	const float Dot = FVector::DotProduct(TargetForwardDirection, TargetToInstigatorDirection);
	
	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	
	if (Dot < 0.5f)
	{
		// Left or Right
		const FVector Cross = FVector::CrossProduct(TargetForwardDirection, TargetToInstigatorDirection);
		
		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}
	return EHitDirection::Forward;
}

FName UStealthBlueprintLibrary::GetHitDirectionName(const EHitDirection HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Back: return FName("Back");
	case EHitDirection::Left: return FName("Left");
	case EHitDirection::Right: return FName("Right");
	case EHitDirection::Forward: return FName("Forward");
	default: return FName("None"); // should not reach here
	}
}

TArray<AActor*> UStealthBlueprintLibrary::HitBoxOverlapTest(AActor* AvatarActor, float HitBoxRadius, float HitBoxForwardOffset, float HitBoxElevationOffset, bool bIsDebugEnabled)
{
	if (!IsValid(AvatarActor)) return TArray<AActor*>();
	
	// Overlap Results
	TArray<FOverlapResult> OverlapResults;
	
	// Pos
	const FVector ForwardDirection = AvatarActor->GetActorForwardVector();
	const FVector HitBoxLocation = AvatarActor->GetActorLocation() + ForwardDirection * HitBoxForwardOffset + HitBoxElevationOffset;
	
	// Collision Shape - Sphere
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	// Query Params
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(AvatarActor);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	// Response Params
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	UWorld* World = GEngine->GetWorldFromContextObject(AvatarActor, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World)) return TArray<AActor*>();
	World->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);
	
	TArray<AActor*> ActorsHit;
	for (const auto& OverlapResult : OverlapResults)
	{
		AStealthBaseCharacter* Character = Cast<AStealthBaseCharacter>(OverlapResult.GetActor());
		if (!IsValid(Character)) continue;
		if (!Character->IsAlive()) continue;
		ActorsHit.AddUnique(Character);
	}
	
	// DEBUG
	if (bIsDebugEnabled)
	{
		DrawHitBoxAndOverlaps(World, OverlapResults, HitBoxLocation, HitBoxRadius);
	}
	
	return ActorsHit;
}

void UStealthBlueprintLibrary::DrawHitBoxAndOverlaps(const UWorld* World, const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation, const float HitBoxRadius)
{
	// Draw HitBox
	DrawDebugSphere(World, HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);
		
	for (auto& OverlapResult : OverlapResults)
	{
		if (!IsValid(OverlapResult.GetActor())) continue;
		DrawDebugSphere(World, OverlapResult.GetActor()->GetActorLocation() 
			+ FVector(0.f, 0.f, 100.f), 30.f, 10, FColor::Green, false, 3.f);
	}
}
