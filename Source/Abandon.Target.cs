// Copyright M9Only

using UnrealBuildTool;
using System.Collections.Generic;

public class AbandonTarget : TargetRules
{
	public AbandonTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Abandon" } );
	}
}
