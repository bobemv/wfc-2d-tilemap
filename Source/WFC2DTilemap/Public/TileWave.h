// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "TileWave.generated.h"

UCLASS()
class WFC2DTILEMAP_API ATileWave : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	TArray<ATile*> PossibleTiles;

	UPROPERTY()
	ATile* SelectedTile;

	UPROPERTY()
	bool bObserved;

	UPROPERTY()
	int X;

	UPROPERTY()
	int Y;

	UPROPERTY()
	int Id;
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

};
