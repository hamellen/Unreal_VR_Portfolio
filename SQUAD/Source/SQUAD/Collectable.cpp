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
	Mesh->SetSimulatePhysics(true);
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectable::NotifyHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, OtherActor, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Get Treasure"));


}



