// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant.h"
#include "lanzadoraLoca.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_USFX_LAB02_API AlanzadoraLoca : public APlant
{
	GENERATED_BODY()
	
public:
AlanzadoraLoca();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Función para disparar en una dirección aleatoria
	UFUNCTION()
	void DispararAleatorio();

private:
};

