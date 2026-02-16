// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StealthGAS	 : ModuleRules
{
	public StealthGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"StealthGAS",
			"StealthGAS/Variant_Platforming",
			"StealthGAS/Variant_Platforming/Animation",
			"StealthGAS/Variant_Combat",
			"StealthGAS/Variant_Combat/AI",
			"StealthGAS/Variant_Combat/Animation",
			"StealthGAS/Variant_Combat/Gameplay",
			"StealthGAS/Variant_Combat/Interfaces",
			"StealthGAS/Variant_Combat/UI",
			"StealthGAS/Variant_SideScrolling",
			"StealthGAS/Variant_SideScrolling/AI",
			"StealthGAS/Variant_SideScrolling/Gameplay",
			"StealthGAS/Variant_SideScrolling/Interfaces",
			"StealthGAS/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
