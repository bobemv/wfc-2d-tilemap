// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ESymmetryType : uint8 {
	X,
	T,
	I,
	L,
	Diagonal
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
	ESymmetryType Symmetry;
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
