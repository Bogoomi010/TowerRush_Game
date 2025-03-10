// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TowerRush : ModuleRules
{
    public TowerRush(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "TowerRush"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
                "GameplayMessageRuntime",
            }
        );
    }
}
