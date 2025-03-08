// Fill out your copyright notice in the Description page of Project Settings.


#include "Magazine.h"
#include "Components/BoxComponent.h"
#include "../Component//GrabComponent.h"
#include "../Player/Squad_Hand.h"
// Sets default values
AMagazine::AMagazine()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Magazine(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SM_AR_01_Magazine_Default.SM_AR_01_Magazine_Default'"));

	

	
	Magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));
	
	GrabComponent = CreateDefaultSubobject<UGrabComponent>(TEXT("GrabComponent"));


	if (SM_Magazine.Succeeded()) {
	
		Magazine->SetStaticMesh(SM_Magazine.Object);
		GrabComponent->SetupAttachment(Magazine);
		
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

void AMagazine::Magazine_Out()
{
	
	GrabComponent->UnBind();
	Magazine->SetCollisionProfileName(TEXT("SquadMagazine"));
	SetLifeSpan(0.5f);
}

void AMagazine::Magazine_In()
{
	GrabComponent->OwingHand = nullptr;
	GrabComponent->bheld = false;
	auto hand = Cast<ASquad_Hand>(GetAttachParentActor());
	if (hand) {
		hand->GrabCom = nullptr;
	}
}

