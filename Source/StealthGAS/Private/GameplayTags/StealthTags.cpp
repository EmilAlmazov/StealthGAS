#include "GameplayTags/StealthTags.h"

namespace StealthTags::StealthAbilities
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "StealthTags.StealthAbilities.Primary", "Tag for Primary Ability");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "StealthTags.StealthAbilities.Secondary", "Tag for Secondary Ability");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "StealthTags.StealthAbilities.Tertiary", "Tag for Tertiary Ability");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "StealthTags.StealthAbilities.ActivateOnGiven", "Tag for abilities that activate as soon as they are given to an actor");
}
