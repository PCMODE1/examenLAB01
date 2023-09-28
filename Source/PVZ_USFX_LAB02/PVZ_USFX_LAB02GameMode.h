// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PVZ_USFX_LAB02GameMode.generated.h"

UCLASS(MinimalAPI)
class APVZ_USFX_LAB02GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APVZ_USFX_LAB02GameMode();

	TArray<class AZombie*> ArrayZombies;
	TArray<class APlant*> ArrayPlants;
	TSubclassOf<ALanzadoraLoca> LanzadoraLocaClass;

	TMap<FString, uint32> MapPotenciadores;

	int32 NumberZombies = 10;
	int32 NumberZombiesSpawned = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	AZombie* SpawnZombie(FVector _spawnPosition);
	APlant* SpawnPlant(FVector _spawnPosition);

	FTimer Temporizador;
	float TiempoTranscurrido = 0.0f;
	float TiempoTranscurridoSiguientePala = 0.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class AlanzadoraLoca> lanzadoraLocaClass;

	void SpawnlanzadoraLoca(const FVector& SpawnLocation);
	
};



