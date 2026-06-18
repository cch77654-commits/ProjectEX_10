using UnrealBuildTool;
using System.Collections.Generic;

public class ModuleAndPluginEditorTarget : TargetRules
{
	public ModuleAndPluginEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[] { "ModuleAndPlugin", "Test" });
	}
}
