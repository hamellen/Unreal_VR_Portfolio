// Fill out your copyright notice in the Description page of Project Settings.


#include "AK_Rifle.h"
#include "Components/BoxComponent.h"
#include "../Component/GrabComponent.h"
#include "../Animation//Rifle_Animinstance.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "../Util/SquadGameInstance.h"
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

	

	
	
}

void AAK_Rifle::BeginPlay()
{
	Super::BeginPlay();
	Gun_Animinstance = Cast<URifle_Animinstance>(main_part->GetAnimInstance());
	current_ammo = max_ammo;
	GrabComponent->grabtrigger.AddUObject(this, &AAK_Rifle::Weapon_Fire);
	Squad_Instance = Cast<USquadGameInstance>(GetWorld()->GetGameInstance());
}

void AAK_Rifle::Weapon_Fire()
{
	gun_muzzle_location = main_part->GetSocketLocation(muzzle_socket);
	gun_muzzle_rotation = main_part->GetSocketRotation(muzzle_socket);

	current_ammo--;
	UGameplayStatics::PlaySoundAtLocation(this, *Squad_Instance->Map_Cue.Find(TEXT("Gun_Fire")), gun_muzzle_location);//소리재생
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), *Squad_Instance->Map_Vfx.Find("Muzzle_Vfx"), gun_muzzle_location, gun_muzzle_rotation);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Location (%f %f %f)"), gun_muzzle_location.X, gun_muzzle_location.Y, gun_muzzle_location.Z));

}

void AAK_Rifle::Reload_Ammo()
{
	Magazine_Position = main_part->GetSocketLocation(magazine_socket);
	current_ammo = max_ammo;
	UGameplayStatics::PlaySoundAtLocation(this, *Squad_Instance->Map_Cue.Find(TEXT("Magazine_In")), Magazine_Position);
}
