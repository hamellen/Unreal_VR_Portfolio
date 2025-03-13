// Fill out your copyright notice in the Description page of Project Settings.


#include "SirenHeader.h"
#include "../Util/Squad_GameMode.h"
#include "Components/AudioComponent.h"
#include "kismet/GameplayStatics.h"
// Sets default values
ASirenHeader::ASirenHeader()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_SIREN(TEXT("/Script/Engine.StaticMesh'/Game/MilitaryAirport/Meshes/Props/SM_FloodLight_2.SM_FloodLight_2'"));

	Siren_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Siren"));
	sound_location = CreateDefaultSubobject<USceneComponent>(TEXT("Sound_Scene"));

	sound_location->SetupAttachment(Siren_Mesh);

	if (SM_SIREN.Succeeded()) {
		Siren_Mesh->SetStaticMesh(SM_SIREN.Object);
	}

}

// Called when the game starts or when spawned
void ASirenHeader::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode_Squad = Cast<ASquad_GameMode>(GetWorld()->GetAuthGameMode());

	GameMode_Squad->Fuc_DeleMulti.AddUObject(this, &ASirenHeader::Play_Siren);
	
}

// Called every frame
void ASirenHeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASirenHeader::Play_Siren()
{
	UGameplayStatics::PlaySoundAtLocation(this, Siren_cue, sound_location->GetComponentLocation());
}

