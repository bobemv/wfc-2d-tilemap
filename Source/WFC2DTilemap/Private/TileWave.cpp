// Fill out your copyright notice in the Description page of Project Settings.


#include "TileWave.h"

// Sets default values
ATileWave::ATileWave()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATileWave::Init(int _X, int _Y, int _Id, TArray<ATile*> _PossibleTiles)
{
	bObserved = false;
	X = _X;
	Y = _Y;
	Id = _Id;
	PossibleTiles = _PossibleTiles;
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

	UE_LOG(LogTemp, Warning, TEXT("TileWave | Id: %d, X: %d, Y: %d, Entropy: %d, isObverved: %d"), Id, X, Y, PossibleTiles.Num(), bObserved);
}

