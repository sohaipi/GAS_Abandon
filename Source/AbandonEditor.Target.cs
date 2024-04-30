// Copyright M9Only

using UnrealBuildTool;
using System.Collections.Generic;

public class AbandonEditorTarget : TargetRules
{
	public AbandonEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Abandon" } );
	}
}
