// Copyright Epic Games, Inc. All Rights Reserved.

#include "PVZ_USFX_LAB02GameMode.h"
#include "PVZ_USFX_LAB02Pawn.h"
#include "Zombie.h"
#include "Plant.h"
#include "lanzadoraLoca.h"

APVZ_USFX_LAB02GameMode::APVZ_USFX_LAB02GameMode()
{
	

	// Set the LanzadoraLoca class
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APVZ_USFX_LAB02Pawn::StaticClass();
	
	// set default pawn class to our character class
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = APVZ_USFX_LAB02Pawn::StaticClass();

	MapPotenciadores.Add(TEXT("Sol"), 0);
	MapPotenciadores.Add(TEXT("Abono"), 1);
	MapPotenciadores.Add(TEXT("Agua"), 2);
	MapPotenciadores.Add(TEXT("Pala"), 0);
}

void APVZ_USFX_LAB02GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (AZombie* ActualZombie : ArrayZombies)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SpawnAfter: %f"), ActualZombie->GetSpawnAfter()));
	
		if (ActualZombie && ActualZombie->SpawnAfter <= 0)
		{
			ActualZombie->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));      // Establece la escala de spawn deseada
			ActualZombie->SetActorHiddenInGame(false);      // Haz que el actor sea visible
			ActualZombie->SetActorEnableCollision(true);     // Habilita las colisiones si es necesario
			ActualZombie->SetCanMove(true);     // Habilita las colisiones si es necesario
			NumberZombiesSpawned += 1;
						
			ArrayZombies.Remove(ActualZombie);
			
		}
		else
		{
			ActualZombie->SpawnAfter -= DeltaTime;
		}

	}
}

void APVZ_USFX_LAB02GameMode::BeginPlay()
{
	Super::BeginPlay();
	

	// Spawnear la planta LanzadoraLoca
	FVector lanzadoraLocaSpawnLocation = FVector(-1000.0f, 1000.0f, 250.0f);  // Ajusta la posición según tus necesidades
	SpawnlanzadoraLoca(lanzadoraLocaSpawnLocation);

	FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(-1500.0f, 1200.0f, 250.0f));
	float initialPositionX = -1500.0f;
	float initialPositionY = 1200.0f;

	for (int32 i = 0; i < NumberZombies; ++i)
	{
		AZombie* NewZombie = SpawnZombie(FVector(initialPositionX + i * 150.0f, initialPositionY, 250.0f));

		if (NewZombie)
		{
			NewZombie->SetSpawnAfter(FMath::RandRange(1, 20));
			NewZombie->SetActorHiddenInGame(true);
			NewZombie->SetActorEnableCollision(false);     // Habilita las colisiones si es necesario
			NewZombie->SetCanMove(false);
			ArrayZombies.Add(NewZombie);
		}
	}


	initialPositionX = -1500.0f;
	initialPositionY = 100.0f;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++) {
			APlant* NewPlant = SpawnPlant(FVector(initialPositionX + i * 150.0f, initialPositionY + j * 350.0f, 250.0f));
			NewPlant->SetActorEnableCollision(true);
			ArrayPlants.Add(NewPlant);
		}
	} 

	initialPositionX = -1500.0f;
	initialPositionY = 1000.0f;
	for (int i = 0; i < 5; i++)
	{
		AZombie* NewZombie = SpawnZombie(FVector(initialPositionX + i * 150.0f, initialPositionY, 250.0f));
		NewZombie->SetCanMove(true);
	}


}

void APVZ_USFX_LAB02GameMode::SpawnlanzadoraLoca(const FVector& SpawnLocation)
{
	if (lanzadoraLocaClass != nullptr)
	{
		AlanzadoraLoca* NewlanzadoraLoca = GetWorld()->SpawnActor<AlanzadoraLoca>(LanzadoraLocaClass, SpawnLocation, FRotator::ZeroRotator);

		if (NewlanzadoraLoca)
		{
			// Iniciar un temporizador para que la LanzadoraLoca dispare en cualquier dirección de manera aleatoria
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, NewlanzadoraLoca, &AlanzadoraLoca::DispararAleatorio, 2.0f, true);
		}
	}
}

AZombie* APVZ_USFX_LAB02GameMode::SpawnZombie(FVector _spawnPosition)
{
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(_spawnPosition);
	return GetWorld()->SpawnActor<AZombie>(AZombie::StaticClass(), SpawnLocation);
}

APlant* APVZ_USFX_LAB02GameMode::SpawnPlant(FVector _spawnPosition)
{
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(_spawnPosition);
	return GetWorld()->SpawnActor<APlant>(APlant::StaticClass(), SpawnLocation);
}