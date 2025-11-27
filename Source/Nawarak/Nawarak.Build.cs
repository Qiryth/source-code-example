// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Nawarak : ModuleRules
{
	public Nawarak(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"AIModule",
			"CommonUI",
			"Core", 
			"CoreUObject", 
			"Engine", 
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayStateTreeModule",
			"GameplayTags",
			"GameplayTasks",
			"InputCore", 
			"NavigationSystem",
			"StateTreeModule",
			"UMG",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
