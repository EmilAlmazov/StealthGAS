#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace StealthTags::StealthAbilities
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
}

namespace StealthTags::StealthAbilities::Player
 {
 	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
 	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary);
 	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary);
 }

namespace StealthTags::Events::Enemy
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
}
