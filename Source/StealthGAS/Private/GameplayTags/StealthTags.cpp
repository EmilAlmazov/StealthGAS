#include "GameplayTags/StealthTags.h"

namespace StealthTags::StealthAbilities
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "StealthTags.StealthAbilities.ActivateOnGiven", "Tag for abilities that activate as soon as they are given to an actor");
}

namespace StealthTags::StealthAbilities::Player
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "StealthTags.StealthAbilities.Player.Primary", "Tag for Primary Ability");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "StealthTags.StealthAbilities.Player.Secondary", "Tag for Secondary Ability");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "StealthTags.StealthAbilities.Player.Tertiary", "Tag for Tertiary Ability");
}

namespace StealthTags::Events
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(CharacterDeath, "StealthTags.Events.CharacterDeath", "Tag for player listening to enemy death");
}

namespace StealthTags::Events::Enemy
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "StealthTags.Events.Enemy.HitReact", "Tag for enemy hit react listen event");
}