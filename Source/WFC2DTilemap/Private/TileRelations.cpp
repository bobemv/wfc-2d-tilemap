// Fill out your copyright notice in the Description page of Project Settings.


#include "TileRelations.h"

TileRelations::TileRelations()
{
	// [0000] [0000] [0000] [0000]
	// [E with E, S, W, N] [S with E, S, W, N] [W with E, S, W, N] [N with E, S, W, N]

	FSymmetryRelation XAndX;
	XAndX.FirstTileSymmetry = ESymmetryType::X;
	XAndX.SecondTileSymmetry = ESymmetryType::X;
	XAndX.RelationMask = 0xFFFF; //1111 1111 1111 1111

	FSymmetryRelation XAndT;
	XAndT.FirstTileSymmetry = ESymmetryType::X;
	XAndT.SecondTileSymmetry = ESymmetryType::T;
	XAndT.RelationMask = 0x1111;//0001 0001 0001 0001

	FSymmetryRelation XAndL;
	XAndL.FirstTileSymmetry = ESymmetryType::X;
	XAndL.SecondTileSymmetry = ESymmetryType::L;
	XAndL.RelationMask = 0x6666;//0110 0110 0110 0110

	FSymmetryRelation XAndI;
	XAndI.FirstTileSymmetry = ESymmetryType::X;
	XAndI.SecondTileSymmetry = ESymmetryType::I;
	XAndI.RelationMask = 0xAAAA;//1010 1010 1010 1010 //TODO

	FSymmetryRelation TAndX;
	TAndX.FirstTileSymmetry = ESymmetryType::T;
	TAndX.SecondTileSymmetry = ESymmetryType::X;
	TAndX.RelationMask = 0x000F;//0000 0000 0000 1111

	FSymmetryRelation TAndT;
	TAndT.FirstTileSymmetry = ESymmetryType::T;
	TAndT.SecondTileSymmetry = ESymmetryType::T;
	TAndT.RelationMask = 0xEEE1; //1110 1110 1110 0001

	FSymmetryRelation TAndL;
	TAndL.FirstTileSymmetry = ESymmetryType::T;
	TAndL.SecondTileSymmetry = ESymmetryType::L;
	TAndL.RelationMask = 0x9996; //1001 1001 1001 0110

	FSymmetryRelation TAndI;
	TAndI.FirstTileSymmetry = ESymmetryType::T;
	TAndI.SecondTileSymmetry = ESymmetryType::I;
	TAndI.RelationMask = 0x555A; //0101 0101 0101 1010 //TODO

	FSymmetryRelation LAndX;
	LAndX.FirstTileSymmetry = ESymmetryType::L;
	LAndX.SecondTileSymmetry = ESymmetryType::X;
	LAndX.RelationMask = 0x0FF0;//0000 1111 1111 0000

	FSymmetryRelation LAndT;
	LAndT.FirstTileSymmetry = ESymmetryType::L;
	LAndT.SecondTileSymmetry = ESymmetryType::T;
	LAndT.RelationMask = 0xE11E; //1110 0001 0001 1110

	FSymmetryRelation LAndL;
	LAndL.FirstTileSymmetry = ESymmetryType::L;
	LAndL.SecondTileSymmetry = ESymmetryType::L;
	LAndL.RelationMask = 0x9669; //1001 0110 0110 1001

	FSymmetryRelation LAndI;
	LAndI.FirstTileSymmetry = ESymmetryType::L;
	LAndI.SecondTileSymmetry = ESymmetryType::I;
	LAndI.RelationMask = 0x5AA5; //0101 1010 1010 0101 //TODO

	FSymmetryRelation IAndX;
	IAndX.FirstTileSymmetry = ESymmetryType::I;
	IAndX.SecondTileSymmetry = ESymmetryType::X;
	IAndX.RelationMask = 0xF0F0;//1111 0000 1111 0000 //TODO

	FSymmetryRelation IAndT;
	IAndT.FirstTileSymmetry = ESymmetryType::I;
	IAndT.SecondTileSymmetry = ESymmetryType::T;
	IAndT.RelationMask = 0x1E1E; //0001 1110 0001 1110 //TODO

	FSymmetryRelation IAndL;
	IAndL.FirstTileSymmetry = ESymmetryType::I;
	IAndL.SecondTileSymmetry = ESymmetryType::L;
	IAndL.RelationMask = 0x6969; //0110 1001 0110 1001 //TODO

	FSymmetryRelation IAndI;
	IAndI.FirstTileSymmetry = ESymmetryType::I;
	IAndI.SecondTileSymmetry = ESymmetryType::I;
	IAndI.RelationMask = 0xA5A5; //1010 0101 1010 0101 //TODO

	SymmetryRelations.Add(XAndX);
	SymmetryRelations.Add(XAndT);
	SymmetryRelations.Add(XAndL);
	SymmetryRelations.Add(XAndI);
	SymmetryRelations.Add(TAndX);
	SymmetryRelations.Add(TAndT);
	SymmetryRelations.Add(TAndL);
	SymmetryRelations.Add(TAndI);
	SymmetryRelations.Add(LAndX);
	SymmetryRelations.Add(LAndT);
	SymmetryRelations.Add(LAndL);
	SymmetryRelations.Add(LAndI);
	SymmetryRelations.Add(IAndX);
	SymmetryRelations.Add(IAndT);
	SymmetryRelations.Add(IAndL);
	SymmetryRelations.Add(IAndI);



	FZoneRelation GrassAndGrass;
	GrassAndGrass.FirstTileZone = EZoneType::Grass;
	GrassAndGrass.SecondTileZone = EZoneType::Grass;
	GrassAndGrass.RelationMask = 0xFFFF; //1111 1111 1111 1111;

	FZoneRelation GrassAndSand;
	GrassAndSand.FirstTileZone = EZoneType::Grass;
	GrassAndSand.SecondTileZone = EZoneType::Sand;
	GrassAndSand.RelationMask = 0x0000; //0000 0000 0000 0000

	FZoneRelation GrassAndGrassSand;
	GrassAndGrassSand.FirstTileZone = EZoneType::Grass;
	GrassAndGrassSand.SecondTileZone = EZoneType::GrassSand;
	GrassAndGrassSand.RelationMask = 0x1111; //0001 0001 0001 0001

	FZoneRelation SandAndGrass;
	SandAndGrass.FirstTileZone = EZoneType::Sand;
	SandAndGrass.SecondTileZone = EZoneType::Grass;
	SandAndGrass.RelationMask = 0x0000; //0000 0000 0000 0000

	FZoneRelation SandAndSand;
	SandAndSand.FirstTileZone = EZoneType::Sand;
	SandAndSand.SecondTileZone = EZoneType::Sand;
	SandAndSand.RelationMask = 0xFFFF; //1111 1111 1111 1111

	FZoneRelation SandAndGrassSand;
	SandAndGrassSand.FirstTileZone = EZoneType::Sand;
	SandAndGrassSand.SecondTileZone = EZoneType::GrassSand;
	SandAndGrassSand.RelationMask = 0x4444; //0100 0100 0100 0100

	FZoneRelation GrassSandAndGrass;
	GrassSandAndGrass.FirstTileZone = EZoneType::GrassSand;
	GrassSandAndGrass.SecondTileZone = EZoneType::Grass;
	GrassSandAndGrass.RelationMask = 0x000F; //0000 0000 0000 1111

	FZoneRelation GrassSandAndSand;
	GrassSandAndSand.FirstTileZone = EZoneType::GrassSand;
	GrassSandAndSand.SecondTileZone = EZoneType::Sand;
	GrassSandAndSand.RelationMask = 0x0F00; //0000 1111 0000 0000

	FZoneRelation GrassSandAndGrassSand;
	GrassSandAndGrassSand.FirstTileZone = EZoneType::GrassSand;
	GrassSandAndGrassSand.SecondTileZone = EZoneType::GrassSand;
	GrassSandAndGrassSand.RelationMask = 0x2481; //0010 0100 1000 0001


	ZoneRelations.Add(GrassAndGrass);
	ZoneRelations.Add(GrassAndSand);
	ZoneRelations.Add(GrassAndGrassSand);
	ZoneRelations.Add(SandAndGrass);
	ZoneRelations.Add(SandAndSand);
	ZoneRelations.Add(SandAndGrassSand);
	ZoneRelations.Add(GrassSandAndGrass);
	ZoneRelations.Add(GrassSandAndSand);
	ZoneRelations.Add(GrassSandAndGrassSand);
}

TileRelations::~TileRelations()
{
}

uint32 TileRelations::GetRelationTileSymmetries(ESymmetryType FirstTileSymmetry, ESymmetryType SecondTileSymmetry)
{
	if (FirstTileSymmetry < SecondTileSymmetry)
	{
		return SymmetryRelations[(int)FirstTileSymmetry * (int)ESymmetryType::MAX + (int)SecondTileSymmetry].RelationMask;
	}
	else {
		return SymmetryRelations[(int)SecondTileSymmetry * (int)ESymmetryType::MAX + (int)FirstTileSymmetry].RelationMask;
	}
}

TArray<FSymmetryRelation> TileRelations::GetAllSymmetryRelationsByTileSymmetry(ESymmetryType TileSymmetry)
{
	TArray<FSymmetryRelation> RelationsFiltered;
	for (int i = 0; i < (int) ESymmetryType::MAX; i++)
	{
		RelationsFiltered.Add(SymmetryRelations[(int)TileSymmetry * (int)ESymmetryType::MAX + i]);
	}

	return RelationsFiltered;
}

bool TileRelations::IsValidTileSymmetriesAndFaces(ESymmetryType FirstTileSymmetry, ESymmetryType SecondTileSymmetry, ETileFaces FirstTileFace, ETileFaces SecondTileFace)
{
	//UE_LOG(LogTemp, Warning, TEXT("TileRelations | Is Valid? FirsTileSymmetry: %d, SecondTileSymmetry: %d, FaceFirstTile: %d, FaceSecondTile: %d"), FirstTileSymmetry, SecondTileSymmetry, FirstTileFace, SecondTileFace);

	uint32 RelationMask = SymmetryRelations[(int)FirstTileSymmetry * (int)ESymmetryType::MAX + (int)SecondTileSymmetry].RelationMask;
	uint32 EvaluationMask = (1 << ((4 * (int)FirstTileFace) + (int)SecondTileFace));
	//UE_LOG(LogTemp, Warning, TEXT("TileRelations | Is Valid? Relation Mask: %d, Evaluation Mask: %d"), RelationMask, EvaluationMask);

	return (RelationMask & EvaluationMask) > 0;
}

bool TileRelations::IsValidTileZonesAndFaces(EZoneType FirstTileZone, EZoneType SecondTileZone, ETileFaces FirstTileFace, ETileFaces SecondTileFace)
{
	//UE_LOG(LogTemp, Warning, TEXT("TileRelations | Is Valid? FirsTileSymmetry: %d, SecondTileZone: %d, FaceFirstTile: %d, FaceSecondTile: %d"), FirstTileZone, SecondTileZone, FirstTileFace, SecondTileFace);

	uint32 RelationMask = ZoneRelations[(int)FirstTileZone * (int)EZoneType::MAX + (int)SecondTileZone].RelationMask;
	uint32 EvaluationMask = (1 << ((4 * (int)FirstTileFace) + (int)SecondTileFace));
	//UE_LOG(LogTemp, Warning, TEXT("TileRelations | Is Valid? Relation Mask: %d, Evaluation Mask: %d"), RelationMask, EvaluationMask);

	return (RelationMask & EvaluationMask) > 0;
}

bool TileRelations::IsValidTileAllRelations(ESymmetryType FirstTileSymmetry, ESymmetryType SecondTileSymmetry, EZoneType FirstTileZone, EZoneType SecondTileZone, ETileFaces FirstTileFace, ETileFaces SecondTileFace)
{
	return IsValidTileSymmetriesAndFaces(FirstTileSymmetry, SecondTileSymmetry, FirstTileFace, SecondTileFace) && IsValidTileZonesAndFaces(FirstTileZone, SecondTileZone, FirstTileFace, SecondTileFace);
}




/*int TileRelations::GetIndexRelation(ESymmetryType FirstTileSymmetry, ESymmetryType SecondTileSymmetry)
{
	int SizeEnumSymmetryType = (int) ESymmetryType::MAX;
	int CounterLoop = 

}*/