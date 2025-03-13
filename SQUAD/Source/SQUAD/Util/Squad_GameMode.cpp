// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad_GameMode.h"
#include "../Monster/EnemySoldier.h"
#include "kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
ASquad_GameMode::ASquad_GameMode()
{


}

void ASquad_GameMode::BeginPlay()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySoldier::StaticClass(), FoundActors);
	count_soldier = FoundActors.Num();
	max_count_soldier = count_soldier;
}

void ASquad_GameMode::DecreaseSoldier()
{
	count_soldier--;
	count_soldier=FMath::Clamp(count_soldier, 0, max_count_soldier);
	if (count_soldier == 0) {
		//사이렌 사운드 재생
		Fuc_DeleMulti.Broadcast();
	}

}
