// Fill out your copyright notice in the Description page of Project Settings.


#include "AK_Rifle.h"
#include "Components/BoxComponent.h"
#include "../Component/GrabComponent.h"
AAK_Rifle::AAK_Rifle()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Main_Sk(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SK_AR_01.SK_AR_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Grip(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Grip_01.SM_ATT_Grip_01'"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Scope(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Scope_02.SM_ATT_Scope_02'"));

	grip_socket = TEXT("Socket_Grip");
	magazine_socket = TEXT("Socket_Magazine");
	scope_socket = TEXT("Socket_Scope");
	muzzle_socket = TEXT("Socket_Muzzle");

	damage = 20.f;

	GrabComponent = CreateDefaultSubobject<UGrabComponent>(TEXT("GrabComponent"));
	main_part = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun_Main"));
	Magazine_box = CreateDefaultSubobject<UBoxComponent>(TEXT("Magazine_Collision"));
	Magazine_box->SetupAttachment(main_part);
	GrabComponent->SetupAttachment(main_part);


	if (Main_Sk.Succeeded()) {

		main_part->SetSkeletalMesh(Main_Sk.Object);
		
	}
	

	grip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grip"));
	if (Grip.Succeeded()) {
	
		grip->SetStaticMesh(Grip.Object);
		grip->SetupAttachment(main_part, grip_socket);
	}


	

	scope = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scope"));
	if (Scope.Succeeded()) {

		scope->SetStaticMesh(Scope.Object);
		scope->SetupAttachment(main_part, scope_socket);
	}

	//GrabComponent->grabtrigger.AddUFunction(this, FName("Weapon_Fire"));
}

void AAK_Rifle::BeginPlay()
{
	Super::BeginPlay();
	current_ammo = max_ammo;
}

void AAK_Rifle::Weapon_Fire()
{
	current_ammo--;

}

void AAK_Rifle::Reload_Ammo()
{
	current_ammo = max_ammo;

}
