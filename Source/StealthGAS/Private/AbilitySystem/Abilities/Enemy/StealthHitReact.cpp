// Copyright Emil Almazov


#include "AbilitySystem/Abilities/Enemy/StealthHitReact.h"

void UStealthHitReact::CalculateAndStoreDirections(const AActor* Instigator)
{
	TargetForwardDirection = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	const FVector TargetLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	TargetToInstigatorDirection = (Instigator->GetActorLocation() - TargetLocation).GetSafeNormal();
}
