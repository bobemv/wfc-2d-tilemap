// Fill out your copyright notice in the Description page of Project Settings.


#include "TileRelations.h"

TileRelations::TileRelations()
{
	// [0000] [0000] [0000] [0000]
	// [E with E, S, W, N] [S with E, S, W, N] [W with E, S, W, N] [N with E, S, W, N]

	FRelation XAndX;
	XAndX.FirstTileSimmetry = ESymmetryType::X;
	XAndX.SecondTileSimmetry = ESymmetryType::X;
	XAndX.RelationMask = 0xFFFF; //1111 1111 1111 1111

	FRelation XAndT;
	XAndT.FirstTileSimmetry = ESymmetryType::X;
	XAndT.SecondTileSimmetry = ESymmetryType::T;
	XAndT.RelationMask = 0x1111;//0001 0001 0001 0001

	FRelation TAndX;
	TAndX.FirstTileSimmetry = ESymmetryType::T;
	TAndX.SecondTileSimmetry = ESymmetryType::X;
	TAndX.RelationMask = 0x000F;//0000 0000 0000 1111

	FRelation TAndT;
	TAndT.FirstTileSimmetry = ESymmetryType::T;
	TAndT.SecondTileSimmetry = ESymmetryType::T;
	TAndT.RelationMask = 0xEEE1; //1110 1110 1110 0001

	Relations.Add(XAndX);
	Relations.Add(XAndT);
	Relations.Add(TAndX);
	Relations.Add(TAndT);

}

TileRelations::~TileRelations()
{
}

uint32 TileRelations::GetRelationTileSimmetries(ESymmetryType FirstTileSimmetry, ESymmetryType SecondTileSimmetry)
{
	if (FirstTileSimmetry < SecondTileSimmetry)
	{
		return Relations[(int)FirstTileSimmetry * (int)ESymmetryType::MAX + (int)SecondTileSimmetry].RelationMask;
	}
	else {
		return Relations[(int)SecondTileSimmetry * (int)ESymmetryType::MAX + (int)FirstTileSimmetry].RelationMask;
	}
}

TArray<FRelation> TileRelations::GetAllRelationsByTileSimmetry(ESymmetryType TileSimmetry)
{
	TArray<FRelation> RelationsFiltered;
	for (int i = 0; i < (int) ESymmetryType::MAX; i++)
	{
		RelationsFiltered.Add(Relations[(int)TileSimmetry * (int)ESymmetryType::MAX + i]);
	}

	return RelationsFiltered;
}

bool TileRelations::IsValidTileSimmetriesAndFaces(ESymmetryType FirstTileSimmetry, ESymmetryType SecondTileSimmetry, int FirstTileFace, int SecondTileFace)
{
	UE_LOG(LogTemp, Warning, TEXT("TileRelations | Is Valid? FirsTileSymmetry: %d, SecondTileSymmetry: %d, FaceFirstTile: %d, FaceSecondTile: %d"), FirstTileSimmetry, SecondTileSimmetry, FirstTileFace, SecondTileFace);

	uint32 RelationMask = Relations[(int)FirstTileSimmetry * (int)ESymmetryType::MAX + (int)SecondTileSimmetry].RelationMask;
	uint32 EvaluationMask = (1 << ((4 * FirstTileFace) + SecondTileFace));
	UE_LOG(LogTemp, Warning, TEXT("TileRelations | Is Valid? Relation Mask: %d, Evaluation Mask: %d"), RelationMask, EvaluationMask);

	return (RelationMask & EvaluationMask) > 0;
}




/*int TileRelations::GetIndexRelation(ESymmetryType FirstTileSimmetry, ESymmetryType SecondTileSimmetry)
{
	int SizeEnumSymmetryType = (int) ESymmetryType::MAX;
	int CounterLoop = 

}*/