// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "Components/SphereComponent.h"
// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	Mesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
	int32 index = FMath::RandRange(0, Mesh_Array.Num() - 1);

	Mesh->SetStaticMesh(Mesh_Array[index]);
	Mesh->SetCollisionProfileName(TEXT("Collectable"));
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

