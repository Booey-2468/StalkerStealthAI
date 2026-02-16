// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StealthAI : ModuleRules
{
	public StealthAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "NavigationSystem", "GameplayTasks" });
	}
}
