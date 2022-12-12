// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MoleWar : ModuleRules
{
	public MoleWar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new string[]
           {
                "MoleWar/",
           });

        PublicDependencyModuleNames.AddRange(new string[] 
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",
            "MoleWar_EditorOnly",
            "MovieSceneTracks",
            "MovieScene",
            "UMG",
        });
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "UnrealEd",
            "Slate",
            "SlateCore",
            "Sequencer",
            "MovieSceneTools"
        });
    }
}
