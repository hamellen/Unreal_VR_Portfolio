// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier_Animinstance.h"
#include "../Monster/EnemySoldier.h"
void USoldier_Animinstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	enemy = Cast<AEnemySoldier>(TryGetPawnOwner());
}

void USoldier_Animinstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (enemy) {
		move_speed = enemy->GetVelocity().Size();
	}

}

void USoldier_Animinstance::Fire()
{

	Montage_Play(Fire_Montage);
}
