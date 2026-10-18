using UnrealBuildTool;
using System.Collections.Generic;

public class BOTOLEditorTarget : TargetRules
{
	public BOTOLEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("BOTOL");
	}
}
