// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class WFC2DTilemapEditorTarget : TargetRules
{
	public WFC2DTilemapEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "WFC2DTilemap" } );
	}
}
