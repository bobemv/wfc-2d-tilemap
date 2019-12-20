// Fill out your copyright notice in the Description page of Project Settings.


#include "WFC.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "TileWave.h"
#include "AssetRegistryModule.h"
#include "Misc/DateTime.h"
#include "HighResScreenshot.h"
#include "ImageUtils.h"
#include "FileHelper.h"
#include "Engine/World.h"
#include "TileRelations.h"

// Sets default values
AWFC::AWFC()
{
	UE_LOG(LogTemp, Warning, TEXT("WFC | Constructor"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(GetRootComponent());

	Height = 2;
	Width = 5;
	TextureDimension = 128;
	
}

// Called when the game starts or when spawned
void AWFC::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("WFC | BeginPlay"));

	Super::BeginPlay();
	CreateTilemap();
	
}

// Called every frame
void AWFC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWFC::CreateTilemap()
{
	//CreateTilemapDefault() -> Array HxW TileWave (it can be all possible tiles)
	//H = 10
	//W = 20
	int ArrayOutputTilemapSize = Height * Width;
	

	UE_LOG(LogTemp, Warning, TEXT("WFC | Creating initial output tilemap"));
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			int Position = (y * Width + x);
			//ATileWave* NewTileWave = NewObject<ATileWave>(this);
			//return (ATileWave*)(GetWorld()->SpawnActor(ATileWave::StaticClass(), NAME_None, GetActorLocation(), GetActorRotation(), NULL, false, false, NULL, NULL));
			ATileWave* NewTileWave = GetWorld()->SpawnActor<ATileWave>(ATileWave::StaticClass(), GetTransform(), FActorSpawnParameters());

			NewTileWave->Init(x, y, Position, Tiles);
			//NewTileWave->Spawn();
			OutputTilemap.Add(NewTileWave);
			//NewTileWave->ToString();

			
		}
	}

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			int Position = (y * Width + x);
			int PositionNorth = ((y + 1) * Width + x);
			int PositionWest = (y * Width + x - 1);
			int PositionSouth = ((y - 1) * Width + x);
			int PositionEast = (y * Width + (x + 1));

			if (PositionNorth >= 0 && PositionNorth < Height * Width && (y + 1) < Height)
			{
				OutputTilemap[Position]->SetTileNorth(OutputTilemap[PositionNorth]);
			}

			if (PositionWest >= 0 && PositionWest < Height * Width && (x - 1) >= 0)
			{
				OutputTilemap[Position]->SetTileWest(OutputTilemap[PositionWest]);
			}

			if (PositionSouth >= 0 && PositionSouth < Height * Width && (y - 1) >= 0)
			{
				OutputTilemap[Position]->SetTileSouth(OutputTilemap[PositionSouth]);
			}
			if (PositionEast >= 0 && PositionEast < Height * Width && (x + 1) < Width)
			{
				OutputTilemap[Position]->SetTileEast(OutputTilemap[PositionEast]);
			}
		}
	}

	int MaxIterations = 5000;
	int CurrentIterations = 0;
	TileRelations TileRelations;
	//LOOP
	while (true)
	{
		CurrentIterations++;
		if (CurrentIterations > MaxIterations)
		{
			UE_LOG(LogTemp, Warning, TEXT("WFC | Maximum iterations reached"));
			break;
		}

		// (Observation phase)
		FIsTileObserved fn;
		// Find TileWave more entropy (= more possible states) or simply a Random TileWave
		TArray<ATileWave*> UnobservedTilesWave = OutputTilemap.FilterByPredicate(fn);
		UE_LOG(LogTemp, Warning, TEXT("WFC | Unobserved tiles wave: %d"), UnobservedTilesWave.Num());
		// IF NOT TileWave with entropy > 0, break loop
		if (UnobservedTilesWave.Num() == 0)
		{
			break;
		}
		UnobservedTilesWave.Sort(LessEntropyComparator);
		//int IndexNextTileWave = FMath::RandRange(0, UnobservedTilesWave.Num() - 1);
		int IndexNextTileWave = 0;
		UE_LOG(LogTemp, Warning, TEXT("WFC | Index next tilewave: %d"), UnobservedTilesWave[IndexNextTileWave]->Id);

		// Collapse. Select a possible Tile for this Tilewave depending on certain condition. Possible conditions:
			// Random tile
			// OR/AND random tile but with weigthed coefficients depending on proportion in input tilemap
			// OR/AND depending on its neighbours in input tilemap
			// OR/AND not using input tilemap and assigning a "symmetry type" to each tile

		int IndexSelectedTile = FMath::RandRange(0, UnobservedTilesWave[IndexNextTileWave]->PossibleTiles.Num() - 1);
		UnobservedTilesWave[IndexNextTileWave]->ObserveTile(TileRelations);


		// (Propagation phase)
			// Propagate information to the rest of tiles to reduce their possibilities by doing
				// Constrain neighbour tiles by reducing its possibilities. Possibilities can NOT be zero for a TileWave. If it happens so, backtrack this step and select other tile for the current Tilewave. Repeat this process as necessary.

			//TODO to be implemented

		// Save change for history [(TileWave with many possibilities -> TileWave with one possibility) + index in history)

			//TODO to be implemented


	}

	// Return output
	//CreateTextureFromOutputTilemap();
			


}

void AWFC::PrintOutputTilemapState()
{
	UE_LOG(LogTemp, Warning, TEXT("WFC | --- Output tilemap state ---"));

	for (auto OutputTile : OutputTilemap)
	{
		OutputTile->ToString();
	}

	UE_LOG(LogTemp, Warning, TEXT("WFC | ------- "));
}

bool AWFC::LessEntropyComparator(ATileWave& ip1, ATileWave& ip2)
{
	return (ip1.GetEntropy() < ip2.GetEntropy());
}