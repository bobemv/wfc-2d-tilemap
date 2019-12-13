// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileWave.h"
#include "TileWaveHistory.generated.h"

UCLASS()
class WFC2DTILEMAP_API ATileWaveHistory : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	ATileWave* TileWaveStart;
	UPROPERTY()
	ATileWave* TileWaveEnd;

public:	
	// Sets default values for this actor's properties
	ATileWaveHistory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
