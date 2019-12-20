// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Tile.h"
#include "TileWave.h"
#include "WFC.generated.h"

USTRUCT()
struct FIsTileObserved {
	GENERATED_BODY()
	bool operator()(ATileWave* TileWave)
	{
		return !TileWave->bObserved;
	}
};

USTRUCT()
struct FGreaterEntropyThan {
	GENERATED_BODY()
		bool operator()(ATileWave* FirstTileWave, ATileWave* SecondTileWave)
	{
		return FirstTileWave->GetEntropy() > SecondTileWave->GetEntropy();
	}
};

UCLASS()
class WFC2DTILEMAP_API AWFC : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Tiles")
	TArray<ATile*> Tiles;

	UPROPERTY(EditAnywhere, Category = "Tiles")
	ATile *Tile;
	UPROPERTY(EditAnywhere, Category = "Tiles")
	int Index;
	UPROPERTY(EditAnywhere, Category = "Tiles")
	int Height;
	UPROPERTY(EditAnywhere, Category = "Tiles")
	int Width;
	UPROPERTY(EditAnywhere, Category = "Tiles")
	int TextureDimension;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USphereComponent* SphereComponent;

public:	
	// Sets default values for this actor's properties
	AWFC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//void CreateTilemap(int HeightTiles, int WidthTiles, TArray<FTile>)
	void CreateTilemap();

	//Variables
	//Array of tiles (pngs)
	//Array Tilemap NxM of said tiles (indexes = order indexes)


	//Functions
	//CreateTilemap(int HeightTiles (H), int WidthTiles (W), Array Tiles, Array InputTilemap)
		//CreateTilemapDefault() -> Array HxW TileWave (it can be all possible tiles)
		//LOOP
			// (Observation phase)
				// Find TileWave more entropy (= more possible states) or simply a Random TileWave
				// IF NOT TileWave with entropy > 0, break loop
				// Collapse. Select a possible Tile for this Tilewave depending on certain condition. Possible conditions:
					// Random tile
					// OR/AND random tile but with weigthed coefficients depending on proportion in input tilemap
					// OR/AND depending on its neighbours in input tilemap
					// OR/AND not using input tilemap and assigning a "symmetry type" to each tile
			// (Propagation phase)
				// Propagate information to the rest of tiles to reduce their possibilities by doing
					// Constrain neighbour tiles by reducing its possibilities. Possibilities can NOT be zero for a TileWave. If it happens so, backtrack this step and select other tile for the current Tilewave. Repeat this process as necessary.
			// Save change for history [(TileWave with many possibilities -> TileWave with one possibility) + index in history)
		// Return output
		//CreatePNGFromOutputTilemap()


	//Structures
		//Tile
			//PNG
			//Index
			//Symmetry Type
		//TileWave
			//Array<int> possibleTileIndexes
			//bObserved
			//int x
			//int y
			//int id
		//TiieWaveHistory
			//TileWaveStart
			//TileWaveEnd
public:
	UPROPERTY(EditAnywhere, Category = "Tiles")
	TArray<ATileWave*> OutputTilemap;
private:
	void PrintOutputTilemapState();
	void CreateTextureFromOutputTilemap();
	bool SaveBitmapAsPNG(int32 sizeX, int32 sizeY, const TArray<FColor>& bitmapData, const FString& filePath);
	inline static bool LessEntropyComparator(ATileWave& ip1, ATileWave& ip2);

};
