// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"


class WFC2DTILEMAP_API TileRelations
{
public:
	TileRelations();
	~TileRelations();

	TArray<FRelation> Relations;

	uint32 GetRelationTileSimmetries(ESymmetryType FirstTileSimmetry, ESymmetryType SecondTileSimmetry);
	TArray<FRelation> GetAllRelationsByTileSimmetry(ESymmetryType TileSimmetry);
	bool IsValidTileSimmetriesAndFaces(ESymmetryType FirstTileSimmetry, ESymmetryType SecondTileSimmetry, int FirstTileFace, int SecondTileFace);

};
