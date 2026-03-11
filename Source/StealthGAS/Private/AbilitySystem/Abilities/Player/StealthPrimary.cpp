// Copyright Emil Almazov


#include "AbilitySystem/Abilities/Player/StealthPrimary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/StealthBaseCharacter.h"
#include "Engine/OverlapResult.h"
#include "GameplayTags/StealthTags.h"

TArray<AActor*> UStealthPrimary::HitBoxOverlapTest()
{
	// Overlap Results
	TArray<FOverlapResult> OverlapResults;
	
	// Pos
	const FVector ForwardDirection = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + ForwardDirection * HitBoxForwardOffset + HitBoxElevationOffset;
	
	// Collision Shape - Sphere
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	// Query Params
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	// Response Params
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);
	
	// DEBUG
	if (IsDebugEnabled())
	{
		DrawHitBoxAndOverlaps(OverlapResults, HitBoxLocation);
	}
	
	TArray<AActor*> ActorsHit;
	for (const auto& OverlapResult : OverlapResults)
	{
		if (!IsValid(OverlapResult.GetActor())) continue;
		
		ActorsHit.AddUnique(OverlapResult.GetActor());
	}
	return ActorsHit;
}

void UStealthPrimary::DrawHitBoxAndOverlaps(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const
{
	// Draw HitBox
	DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);
		
	for (auto& OverlapResult : OverlapResults)
	{
		if (!IsValid(OverlapResult.GetActor())) continue;
		DrawDebugSphere(GetWorld(), OverlapResult.GetActor()->GetActorLocation() + FVector(0.f, 0.f, 100.f), 30.f, 10, FColor::Green, false, 3.f);
	}
}

void UStealthPrimary::SendHitReactEventToEnemy(const TArray<AActor*>& ActorsHit)
{
	for (auto& ActorHit : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ActorHit, StealthTags::Events::Enemy::HitReact, Payload);
	}
}
