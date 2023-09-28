// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "lanzadoraLoca.h"

AlanzadoraLoca::AlanzadoraLoca()
{
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlantMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim.Shape_Trim'"));
	PlantMeshComponent->SetStaticMesh(PlantMesh.Object);

	Tags.Add(TEXT("LanzadoraLoca"));
    PrimaryActorTick.bCanEverTick = true;

   
}