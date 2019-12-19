// Fill out your copyright notice in the Description page of Project Settings.


#include "TileWave.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "TileRelations.h"

// Sets default values
ATileWave::ATileWave()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* Asset = MeshAsset.Object;

	StaticMeshComponent->SetStaticMesh(Asset);
	ScaleZ = 0.01f;
	CellSizeX = 100;
	CellSizeY = 100;


	SetActorScale3D(FVector(1.0f, 1.0f, ScaleZ));



}

void ATileWave::Init(int _X, int _Y, int _Id, TArray<ATile*> _PossibleTiles)
{
	bObserved = false;
	X = _X;
	Y = _Y;
	Id = _Id;
	PossibleTiles = _PossibleTiles;
	SetActorLocation(FVector(- CellSizeX * X, CellSizeY * Y, 0));
}

// Called when the game starts or when spawned
void ATileWave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileWave::ToString()
{

	UE_LOG(LogTemp, Warning, TEXT("TileWave | Id: %d, X: %d, Y: %d, Entropy: %d, isObserved: %d"), Id, X, Y, PossibleTiles.Num(), bObserved);
}

void ATileWave::ObserveTile(TileRelations TileRelations)
{
	bObserved = true;

	UE_LOG(LogTemp, Warning, TEXT("TileWave | Observing Tile Wave in X: %d, Y: %d"), X, Y);

	TArray<FRelation> RelationsTileNorth, RelationsTileWest, RelationsTileSouth, RelationsTileEast;
	int FaceTileNorthToTile = 0, FaceTileWestToTile = 0, FaceTileSouthToTile = 0, FaceTileEastToTile = 0;
	TArray<ESymmetryType> PossibleTileSimmetriesDependingOnNeighbours;

	if (TileNorth != nullptr && TileNorth->SelectedTile != nullptr)
	{
		RelationsTileNorth = TileRelations.GetAllRelationsByTileSimmetry(TileNorth->SelectedTile->Simmetry);
		for (FRelation RelationTileNorth : RelationsTileNorth)
		{
			PossibleTileSimmetriesDependingOnNeighbours.AddUnique(RelationTileNorth.SecondTileSimmetry);
		}
		FaceTileNorthToTile = Mod(2 - TileNorth->Rotation, 4); // O NORTH, 1 WEST, 2 SOUTH, 3 EAST - 0 NO ROTATION, 1 ROTATION 90º COUNTERCLOCKWISE, 2 ROTATION 180º COUNTERCLOCKWISE, 3 ROTATION 270º COUNTERCLOCKWISE, 
		UE_LOG(LogTemp, Warning, TEXT("TileWave | Tile in North exists. Symmetry: %d. Face To Tile: %d"), TileNorth->SelectedTile->Simmetry, FaceTileNorthToTile);
	}

	if (TileWest != nullptr && TileWest->SelectedTile != nullptr)
	{
		RelationsTileWest = TileRelations.GetAllRelationsByTileSimmetry(TileWest->SelectedTile->Simmetry);
		for (FRelation RelationTileWest : RelationsTileWest)
		{
			PossibleTileSimmetriesDependingOnNeighbours.AddUnique(RelationTileWest.SecondTileSimmetry);
		}
		FaceTileWestToTile = Mod(3 - TileWest->Rotation, 4); //0000 0001 EAST
		UE_LOG(LogTemp, Warning, TEXT("TileWave | Tile in West exists. Symmetry: %d. Face To Tile: %d"), TileWest->SelectedTile->Simmetry, FaceTileWestToTile);

	}

	if (TileSouth != nullptr && TileSouth->SelectedTile != nullptr)
	{
		RelationsTileSouth = TileRelations.GetAllRelationsByTileSimmetry(TileSouth->SelectedTile->Simmetry);
		for (FRelation RelationTileSouth : RelationsTileSouth)
		{
			PossibleTileSimmetriesDependingOnNeighbours.AddUnique(RelationTileSouth.SecondTileSimmetry);
		}
		FaceTileSouthToTile = Mod(0 - TileSouth->Rotation, 4); //0000 1000 NORTH
		UE_LOG(LogTemp, Warning, TEXT("TileWave | Tile in South exists. Symmetry: %d. Face To Tile: %d"), TileSouth->SelectedTile->Simmetry, FaceTileSouthToTile);
	}
	if (TileEast != nullptr && TileEast->SelectedTile != nullptr)
	{
		RelationsTileEast = TileRelations.GetAllRelationsByTileSimmetry(TileEast->SelectedTile->Simmetry);
		for (FRelation RelationTileEast : RelationsTileEast)
		{

			PossibleTileSimmetriesDependingOnNeighbours.AddUnique(RelationTileEast.SecondTileSimmetry);
		}
		FaceTileEastToTile = Mod(1 - TileEast->Rotation, 4); //0000 0100 WEST
		UE_LOG(LogTemp, Warning, TEXT("TileWave | Tile in East exists. Symmetry: %d. Face To Tile: %d"), TileEast->SelectedTile->Simmetry, FaceTileEastToTile);
	}

	ATile* TileObserved = nullptr;
	int RotationIndex = 0;
	TArray<FTileWavePossibility> TileWavePossibilities;

	PossibleTileSimmetriesDependingOnNeighbours = { ESymmetryType::T, ESymmetryType::X };
	UE_LOG(LogTemp, Warning, TEXT("TileWave | Number of Possible Tile Symmetries: %d"), PossibleTileSimmetriesDependingOnNeighbours.Num());

	//Point where can be RANDOMIZED or DETERMINISTIC
	for (ESymmetryType PossibleSimmetry : PossibleTileSimmetriesDependingOnNeighbours)
	{
		bool isSymmetryValid = false;
		RotationIndex = 0;
		UE_LOG(LogTemp, Warning, TEXT("TileWave | Possible Tile Symmetry: %d"), PossibleSimmetry);

		for (RotationIndex = 0; RotationIndex < 4; RotationIndex++)
		{
			UE_LOG(LogTemp, Warning, TEXT("TileWave | Rotation Possible Tile Symmetry: %d"), RotationIndex);

			bool isSymmetryRotationValid = true;
			if (TileNorth != nullptr && TileNorth->SelectedTile != nullptr)
			{
				isSymmetryRotationValid &= TileRelations.IsValidTileSimmetriesAndFaces(PossibleSimmetry, TileNorth->SelectedTile->Simmetry, Mod(0 - RotationIndex, 4), FaceTileNorthToTile);
			}

			if (TileWest != nullptr && TileWest->SelectedTile != nullptr)
			{
				isSymmetryRotationValid &= TileRelations.IsValidTileSimmetriesAndFaces(PossibleSimmetry, TileWest->SelectedTile->Simmetry, Mod(1 - RotationIndex, 4), FaceTileWestToTile);
			}

			if (TileSouth != nullptr && TileSouth->SelectedTile != nullptr)
			{
				isSymmetryRotationValid &= TileRelations.IsValidTileSimmetriesAndFaces(PossibleSimmetry, TileSouth->SelectedTile->Simmetry, Mod(2 - RotationIndex, 4), FaceTileSouthToTile);
			}
			if (TileEast != nullptr && TileEast->SelectedTile != nullptr)
			{
				isSymmetryRotationValid &= TileRelations.IsValidTileSimmetriesAndFaces(PossibleSimmetry, TileEast->SelectedTile->Simmetry, Mod(3 - RotationIndex, 4), FaceTileEastToTile);
			}
			if (isSymmetryRotationValid)
			{
				UE_LOG(LogTemp, Warning, TEXT("TileWave | Tile Symmetry FOUND: %d with Rotation: %d"), PossibleSimmetry, RotationIndex);
				FTileWavePossibility TileWavePossibility;
				TileWavePossibility.Symmetry = PossibleSimmetry;
				TileWavePossibility.Rotation = RotationIndex;
				TileWavePossibilities.Add(TileWavePossibility);
			}
		}
	}

	if (TileWavePossibilities.Num() > 0)
	{
		int IndexTileWavePossibilitySelected = FMath::RandRange(0, TileWavePossibilities.Num() - 1);
		FTileWavePossibility TileWavePossibilitySelected = TileWavePossibilities[IndexTileWavePossibilitySelected];
		ESymmetryType SymmetrySelected = TileWavePossibilitySelected.Symmetry;
		TArray<ATile*> PossibleTilesMatchingSymmetry;
		UE_LOG(LogTemp, Warning, TEXT("TileWave | Searching Tile with Symmetry found"));
		//GET RANDOM OR FIRST TILE WHICH MATCHES SYMMETRY
		for (int i = 0; i < PossibleTiles.Num(); i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("TileWave | Possibb Tile with Symmetry: %d"), PossibleTiles[i]->Index);

			if (PossibleTiles[i]->Simmetry == SymmetrySelected)
			{
				PossibleTilesMatchingSymmetry.Add(PossibleTiles[i]);
				UE_LOG(LogTemp, Warning, TEXT("TileWave | Tile SELECTED: %d"), PossibleTiles[i]->Index);

				//TileObserved = PossibleTiles[i];
			}
		}

		if (PossibleTilesMatchingSymmetry.Num() > 0)
		{
			int IndexTileWaveSelected = FMath::RandRange(0, PossibleTilesMatchingSymmetry.Num() - 1);
			SelectedTile = PossibleTilesMatchingSymmetry[IndexTileWaveSelected];
			StaticMeshComponent->SetMaterial(0, SelectedTile->Material);
			AddActorWorldRotation(FRotator(0, -90 * TileWavePossibilitySelected.Rotation, 0));
			Rotation = TileWavePossibilitySelected.Rotation;
		}
	}

	TileNorth->TileSouthHasBeenUpdated();
	TileEast->TileWestHasBeenUpdated();
	TileSouth->TileNorthHasBeenUpdated();
	TileWest->TileEastHasBeenUpdated();
}

void ATileWave::TileNorthHasBeenUpdated()
{
	return;
}
void ATileWave::TileWestHasBeenUpdated()
{
	return;
}
void ATileWave::TileSouthHasBeenUpdated()
{
	return;
}
void ATileWave::TileEastHasBeenUpdated()
{
	return;
}

int ATileWave::Mod(int x, int N) {
	return (x % N + N) % N;
}

float ATileWave::GetEntropy() {
	int EntropyCounter = 0;

	if (TileNorth == nullptr || TileNorth->SelectedTile == nullptr)
	{
		EntropyCounter++;
	}

	if (TileWest == nullptr || TileWest->SelectedTile == nullptr)
	{
		EntropyCounter++;
	}

	if (TileSouth == nullptr || TileSouth->SelectedTile == nullptr)
	{
		EntropyCounter++;
	}
	if (TileEast == nullptr || TileEast->SelectedTile == nullptr)
	{
		EntropyCounter++;
	}
	return EntropyCounter;
}