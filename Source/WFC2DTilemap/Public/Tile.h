// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ESymmetryType : uint8 {
	X,
	T,
	L,
	I,
	MAX
};

UENUM()
enum class EZoneType : uint8 {
	Grass,
	Sand,
	GrassSand,
	MAX
};

UENUM()
enum class ETileFaces : uint8 {
	North,
	West,
	South,
	East,
	MAX
};

USTRUCT()
struct FSymmetryRelation {

	GENERATED_BODY()
public:
	UPROPERTY()
	ESymmetryType FirstTileSymmetry;
	UPROPERTY()
	ESymmetryType SecondTileSymmetry;
	UPROPERTY()
	uint16 RelationMask;
};

USTRUCT()
struct FZoneRelation {

	GENERATED_BODY()
public:
	UPROPERTY()
	EZoneType FirstTileZone;
	UPROPERTY()
	EZoneType SecondTileZone;
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
	class UMaterialInterface* Material;

	UPROPERTY(EditAnywhere)
	ESymmetryType Symmetry;

	UPROPERTY(EditAnywhere)
	EZoneType Zone;


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
