// Copyright Emil Almazov


#include "Util/StealthBlueprintLibrary.h"

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