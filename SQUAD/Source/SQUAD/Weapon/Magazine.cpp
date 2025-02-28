// Fill out your copyright notice in the Description page of Project Settings.


#include "Magazine.h"
#include "Components/BoxComponent.h"
// Sets default values
AMagazine::AMagazine()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Magazine(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SM_AR_01_Magazine_Default.SM_AR_01_Magazine_Default'"));

	

	
	Magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));
	

	if (SM_Magazine.Succeeded()) {
	
		Magazine->SetStaticMesh(SM_Magazine.Object);
		
	}
	


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMagazine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagazine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

