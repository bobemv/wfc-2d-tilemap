// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"


class WFC2DTILEMAP_API TileRelations
{
public:
	TileRelations();
	~TileRelations();

	TArray<FSymmetryRelation> SymmetryRelations;
	TArray<FZoneRelation> ZoneRelations;

	uint32 GetRelationTileSymmetries(ESymmetryType FirstTileSymmetry, ESymmetryType SecondTileSymmetry);
	TArray<FSymmetryRelation> GetAllSymmetryRelationsByTileSymmetry(ESymmetryType TileSymmetry);
	bool IsValidTileSymmetriesAndFaces(ESymmetryType FirstTileSymmetry, ESymmetryType SecondTileSymmetry, ETileFaces FirstTileFace, ETileFaces SecondTileFace);
	bool IsValidTileZonesAndFaces(EZoneType FirstTileZone, EZoneType SecondTileZone, ETileFaces FirstTileFace, ETileFaces SecondTileFace);
	bool IsValidTileAllRelations(ESymmetryType FirstTileSymmetry, ESymmetryType SecondTileSymmetry, EZoneType FirstTileZone, EZoneType SecondTileZone, ETileFaces FirstTileFace, ETileFaces SecondTileFace);
};
