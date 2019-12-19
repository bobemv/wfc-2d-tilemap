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
		//FGreaterEntropyThan GreaterEntropyThanFunction;
		UnobservedTilesWave.Sort(ConstPredicate);
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

void AWFC::CreateTextureFromOutputTilemap()
{

	int WidthPixels = Width * TextureDimension;
	int HeightPixels = Height * TextureDimension;
	//Creating the UTexture2D object
	FString TextureName = "WFCOutput_";
	TextureName.Append(FString::FromInt(FDateTime::Now().ToUnixTimestamp()));
	TextureName.Append(".png");
	FString PackageName = TEXT("/Game/ProceduralTextures/");
	//PackageName += TextureName;
	//UPackage* Package = CreatePackage(NULL, *PackageName);
	//Package->FullyLoad();

	//UTexture2D* NewTexture = NewObject<UTexture2D>(Package, *TextureName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

	//Filling the texture with our data
	// - Configuring texture
	/*NewTexture->AddToRoot();				// This line prevents garbage collection of the texture
	NewTexture->PlatformData = new FTexturePlatformData();	// Then we initialize the PlatformData
	NewTexture->PlatformData->SizeX = WidthPixels;
	NewTexture->PlatformData->SizeY = HeightPixels;
	NewTexture->PlatformData->NumSlices = 1;
	NewTexture->PlatformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;*/

	// - Getting the data for our texture
	/* ---- 1 ----
	/*uint8* Pixels = new uint8[WidthPixels * HeightPixels * 4];
	for (int32 y = 0; y < (HeightPixels); y++)
	{
		for (int32 x = 0; x < (WidthPixels); x++)
		{
			int32 curPixelIndex = ((y * WidthPixels) + x);
			Pixels[4 * curPixelIndex] = 0x00;
			Pixels[4 * curPixelIndex + 1] = 0xA0;
			Pixels[4 * curPixelIndex + 2] = 0xE2;
			Pixels[4 * curPixelIndex + 3] = 0xFF;
		}
	}*/

	TArray<FColor> OutBMP;
	int NewTextureWidhtPixels = Width * TextureDimension;
	int NewTexturHeightPixels = Height * TextureDimension;
	int NewTextureTotalPixels = NewTextureWidhtPixels * NewTexturHeightPixels;
	int NewTextureTotalPixelsByColor = NewTextureTotalPixels * 4;
	int TileTotalPixels = TextureDimension * TextureDimension;
	int TileTotalPixelsByColor = TileTotalPixels * 4;
	int TileRowTotalPixels = TileTotalPixels * Width;
	int TileRowTotalPixelsByColor = TileRowTotalPixels * 4;

	OutBMP.SetNumUninitialized(NewTextureWidhtPixels * NewTexturHeightPixels);

	//uint8* Pixels = new uint8[NewTextureTotalPixelsByColor];
	for (int32 IndexTilesY = 0; IndexTilesY < Height; IndexTilesY++)
	{
		for (int32 IndexTilesX = 0; IndexTilesX < Width; IndexTilesX++)
		{

			int IndexCurrentTile = (IndexTilesY * Width) + IndexTilesX;


			if (OutputTilemap[IndexCurrentTile]->SelectedTile == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("WFC | Selected tile failed to load in X: %d, Y: %d"), IndexTilesX, IndexTilesY);
				continue;
			}

			UTexture2D* TextureTile = OutputTilemap[IndexCurrentTile]->SelectedTile->Image;

			if (TextureTile == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("WFC | Texture failed to load in X: %d, Y: %d"), IndexTilesX, IndexTilesY);
				continue;
			}


			FTexture2DMipMap* MyMipMap = &TextureTile->PlatformData->Mips[0];
			FUntypedBulkData* RawImageData = &MyMipMap->BulkData;
			FColor* FormatedImageData = static_cast<FColor*>(RawImageData->Lock(LOCK_READ_ONLY));

			//const FColor* FormatedImageData = static_cast<const FColor*>(MipData);



			//int32 OutputTexturePixelStart = ((IndexTilesY * Width * TextureDimension * TextureDimension) + IndexTilesX * TextureDimension * TextureDimension);


			for (int32 IndexPixelTileX = 0; IndexPixelTileX < TextureTile->GetSizeX(); IndexPixelTileX++)
			{
				for (int32 IndexPixelTileY = 0; IndexPixelTileY < TextureTile->GetSizeY(); IndexPixelTileY++)
				{
					int32 IndexPixel = IndexPixelTileY * TextureTile->GetSizeX() + IndexPixelTileX;
					FColor PixelColor = FormatedImageData[IndexPixel];


					/*IndexPixelTileY * TextureDimension * Width * 4

					IndexPixelTileX
					????*/

					int IndexPixelOutput = IndexTilesY * TileRowTotalPixels + IndexTilesX * TextureDimension + IndexPixelTileY * TextureDimension * Width + IndexPixelTileX;

					/*
					Pixels[OutputTexturePixelStart + 4 * IndexPixel] = PixelColor.R;
					Pixels[OutputTexturePixelStart + 4 * IndexPixel + 1] = PixelColor.G;
					Pixels[OutputTexturePixelStart + 4 * IndexPixel + 2] = PixelColor.B;
					Pixels[OutputTexturePixelStart + 4 * IndexPixel + 3] = PixelColor.A;
					*/

					//Pixels[IndexPixelOutput] = PixelColor.B;
					//Pixels[IndexPixelOutput + 1] = PixelColor.G;
					//Pixels[IndexPixelOutput + 2] = PixelColor.R;
					//Pixels[IndexPixelOutput + 3] = PixelColor.A;
					OutBMP[IndexPixelOutput] = FormatedImageData[0];
					// Do the job with the pixel
				}
			}

			TextureTile->PlatformData->Mips[0].BulkData.Unlock();

		}
	}

	//FIntPoint DestSize(NewTextureWidhtPixels, NewTexturHeightPixels);

	FString ResultPath = "";
	//FHighResScreenshotConfig& HighResScreenshotConfig = GetHighResScreenshotConfig();
	//SaveBitmapAsPNG(NewTextureWidhtPixels, NewTexturHeightPixels, OutBMP, ResultPath);
	SaveBitmapAsPNG(NewTextureWidhtPixels, NewTexturHeightPixels, OutBMP, PackageName);
	
	/*

	// - populating our texture with our data
	// Allocate first mipmap.
	FTexture2DMipMap* Mip = new(NewTexture->PlatformData->Mips) FTexture2DMipMap();
	Mip->SizeX = WidthPixels;
	Mip->SizeY = HeightPixels;

	// Lock the texture so it can be modified
	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = (uint8*)Mip->BulkData.Realloc(WidthPixels * HeightPixels * 4);
	FMemory::Memcpy(TextureData, Pixels, sizeof(uint8) * HeightPixels * WidthPixels * 4);
	Mip->BulkData.Unlock();

	// Saving the texture

	NewTexture->Source.Init(WidthPixels, HeightPixels, 1, 1, ETextureSourceFormat::TSF_BGRA8, Pixels);

	NewTexture->UpdateResource();
	Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(NewTexture);

	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	bool bSaved = UPackage::SavePackage(Package, NewTexture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);
	*/


	//delete[] Pixels;	// Don't forget to free the memory here

}

bool AWFC::SaveBitmapAsPNG(int32 sizeX, int32 sizeY, const TArray<FColor>& bitmapData, const FString& filePath) {
	TArray<uint8> compressedBitmap;
	FImageUtils::CompressImageArray(sizeX, sizeY, bitmapData, compressedBitmap);
	return FFileHelper::SaveArrayToFile(compressedBitmap, *filePath);
}

bool AWFC::ConstPredicate(ATileWave& ip1, ATileWave& ip2)
{
	return (ip1.GetEntropy() < ip2.GetEntropy());
}