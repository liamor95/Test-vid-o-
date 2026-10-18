using UnrealBuildTool;

public class BOTOL : ModuleRules
{
	public BOTOL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem"
		});

		// Permet d'inclure "Units/BotolUnit.h", "Player/..." depuis n'importe quel fichier du module.
		PublicIncludePaths.Add(ModuleDirectory);
	}
}
