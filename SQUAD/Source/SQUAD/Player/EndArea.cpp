// Fill out your copyright notice in the Description page of Project Settings.


#include "EndArea.h"
#include "Components/BoxComponent.h"
#include "../Player/Squad_Pawn.h"
#include "../Collectable.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/Squad_Pawn.h"
#include "../Util/Squad_GameMode.h"

// Sets default values
AEndArea::AEndArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
}

// Called when the game starts or when spawned
void AEndArea::BeginPlay()
{
	Super::BeginPlay();
	
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEndArea::OnOverlapBegin);

}

// Called every frame
void AEndArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ASquad_Pawn::StaticClass())) {
	
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectable::StaticClass(), FoundActors);
		if (FoundActors.Num() == 0) {
			auto gamemode = Cast<ASquad_GameMode>(GetWorld()->GetAuthGameMode());
			gamemode->StopTime();
			auto pawn = Cast<ASquad_Pawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquad_Pawn::StaticClass()));
			pawn->Spawn_Last_Menu();
			
		}
	}

}

