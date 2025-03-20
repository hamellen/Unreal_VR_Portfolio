// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier_Animinstance.h"
#include "../Monster/EnemySoldier.h"
#include "../Weapon/Bullet.h"
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
		ReadyToFire = enemy->ReadyToFire;
	}

}

void USoldier_Animinstance::AnimNotify_bullet_fire()
{
	FVector socket_location =enemy-> gun_mesh->GetSocketLocation(TEXT("Socket_Muzzle"));
	FRotator socket_rotation = enemy->GetActorRotation();

	GetWorld()->SpawnActor<ABullet>(enemy->bullet_class, socket_location, socket_rotation);//醚舅 积己

}

void USoldier_Animinstance::Fire()
{

	Montage_Play(Fire_Montage);//根鸥瘤 犁积


}
