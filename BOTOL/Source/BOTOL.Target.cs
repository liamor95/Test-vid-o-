using UnrealBuildTool;
using System.Collections.Generic;

public class BOTOLTarget : TargetRules
{
	public BOTOLTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("BOTOL");
	}
}
