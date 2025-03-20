// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad_GameMode.h"
#include "../Monster/EnemySoldier.h"
#include "kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "../Collectable.h"
#include "Engine/TargetPoint.h"
#include "TimerManager.h"
ASquad_GameMode::ASquad_GameMode()
{
	static ConstructorHelpers::FClassFinder<AEnemySoldier>cl_soldier(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_EnemySoldier.BP_EnemySoldier_C'"));


	if (cl_soldier.Succeeded()) {
		class_soldier = cl_soldier.Class;
		}
}

void ASquad_GameMode::BeginPlay()
{
	


	TArray<AActor*> Treasures ;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectable::StaticClass(), Treasures);
	count_Treasure = Treasures.Num();
	
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Target);
	
	
	

	
}



void ASquad_GameMode::Left_Treasure()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("GetTreasure"));

	count_Treasure--;
	count_Treasure = FMath::Clamp(count_Treasure,0,INT32_MAX);
	Fuc_Treasure.Broadcast();
	if (count_Treasure == 0) {
		//사이렌 사운드 재생
		
		Fuc_DeleMulti.Broadcast();
		SpawnSoldier();
	}

}

void ASquad_GameMode::SpawnSoldier()
{
	for (AActor* TargetActor : Target)
	{
		ATargetPoint* TargetPoint = Cast<ATargetPoint>(TargetActor);
		if (TargetPoint)
		{

			GetWorld()->SpawnActor<AEnemySoldier>(
				class_soldier,
				TargetPoint->GetActorLocation(),
				TargetPoint->GetActorRotation()
			);


		}
	}

}


