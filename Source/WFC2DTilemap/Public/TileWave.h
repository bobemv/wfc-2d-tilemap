// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "TileRelations.h"
#include "TileWave.generated.h"

USTRUCT()
struct FTileWavePossibility {
	GENERATED_BODY()

	UPROPERTY()
	ESymmetryType Symmetry;
	UPROPERTY()
	EZoneType Zone;
	UPROPERTY()
	ETileFaces Rotation;
};

UCLASS()
class WFC2DTILEMAP_API ATileWave : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
	TArray<ATile*> PossibleTiles;

	UPROPERTY(VisibleAnywhere)
	ATile* SelectedTile;

	UPROPERTY(VisibleAnywhere)
	ATileWave* TileNorth;
	UPROPERTY(VisibleAnywhere)
	ATileWave* TileWest;
	UPROPERTY(VisibleAnywhere)
	ATileWave* TileSouth;
	UPROPERTY(VisibleAnywhere)
	ATileWave* TileEast;

	UPROPERTY(VisibleAnywhere)
	bool bObserved;

	UPROPERTY(VisibleAnywhere)
	int X;

	UPROPERTY(VisibleAnywhere)
	int Y;

	UPROPERTY(VisibleAnywhere)
	int Id;

	UPROPERTY(VisibleAnywhere)
	ETileFaces Rotation;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Tile | Properties")
	float ScaleZ;

	UPROPERTY(EditAnywhere, Category = "Tile | Properties")
	int CellSizeX;

	UPROPERTY(EditAnywhere, Category = "Tile | Properties")
	int CellSizeY;

public:	
	ATileWave();
	// Sets default values for this actor's properties

	void Init(int _X, int _Y, int _Id, TArray<ATile*> _PossibleTiles);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ToString();
	void ObserveTile(TileRelations TileRelations);

	void TileNorthHasBeenUpdated();
	void TileWestHasBeenUpdated();
	void TileSouthHasBeenUpdated();
	void TileEastHasBeenUpdated();
	float GetEntropy();

	FORCEINLINE void SetTileNorth(ATileWave* NewTileNorth) { TileNorth = NewTileNorth; };
	FORCEINLINE void SetTileWest(ATileWave* NewTileWest) { TileWest = NewTileWest; };
	FORCEINLINE void SetTileSouth(ATileWave* NewTileSouth) { TileSouth = NewTileSouth; };
	FORCEINLINE void SetTileEast(ATileWave* NewTileEast) { TileEast = NewTileEast; };

private:
	uint8 ChangeFaceMaskDependingOnRotation(uint8 FaceMask);
	int Mod(int x, int N);

};
