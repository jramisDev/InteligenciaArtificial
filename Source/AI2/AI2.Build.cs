// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI2 : ModuleRules
{
	public AI2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
        
        PublicIncludePaths.AddRange(new string[]
        {
        	"AI2/Public"
        });
	}
}
