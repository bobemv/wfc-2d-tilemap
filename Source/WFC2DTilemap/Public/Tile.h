// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ESymmetryType : uint8 {
	X,
	T,
	MAX
};

UENUM()
enum class ETileFaces : uint8 {
	North,
	West,
	South,
	East,
};

USTRUCT()
struct FRelation {

	GENERATED_BODY()
public:
	UPROPERTY()
	ESymmetryType FirstTileSimmetry;
	UPROPERTY()
	ESymmetryType SecondTileSimmetry;
	UPROPERTY()
	uint16 RelationMask;
};

UCLASS()
class WFC2DTILEMAP_API ATile : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int Index;

	UPROPERTY(EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* Material;

	UPROPERTY(EditAnywhere)
	ESymmetryType Simmetry;


public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
