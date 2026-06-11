// Copyright Emil Almazov


#include "AbilitySystem/Abilities/Player/StealthPrimary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTags/StealthTags.h"

void UStealthPrimary::SendHitReactEventToEnemy(const TArray<AActor*>& ActorsHit)
{
	for (auto& ActorHit : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ActorHit, StealthTags::Events::Enemy::HitReact, Payload);
	}
}
