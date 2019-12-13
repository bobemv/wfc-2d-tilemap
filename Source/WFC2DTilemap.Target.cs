// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class WFC2DTilemapTarget : TargetRules
{
	public WFC2DTilemapTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "WFC2DTilemap" } );
	}
}
