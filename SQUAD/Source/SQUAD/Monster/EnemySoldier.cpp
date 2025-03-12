// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"
#include "../Component/StatComponent.h"
#include "../Weapon/AK_Rifle.h"
#include "Enemy_Controller.h"
#include "../Weapon/Bullet.h"
#include "../Animation/Soldier_Animinstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Animation/Soldier_Animinstance.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
// Sets default values
AEnemySoldier::AEnemySoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ABullet>bullet(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Bullet_Enemy.BP_Bullet_Enemy_C'"));

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);

	stat = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));
	gun_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GUN"));
	if (bullet.Succeeded()) {
		bullet_class = bullet.Class;
	}
	
	gun_mesh->SetupAttachment(GetMesh(), TEXT("Weapon_Socket"));
	
}

// Called when the game starts or when spawned
void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;


	int32 index = FMath::RandRange(0, sk_array.Num() - 1);

	GetMesh()->SetSkeletalMesh(sk_array[index]);

	soldier_anim = Cast<USoldier_Animinstance>(GetMesh()->GetAnimInstance());

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemySoldier::OnHit);


	soldier_anim->OnMontageEnded.AddDynamic(this, &AEnemySoldier::OnMontageEnded);
}

// Called every frame
void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemySoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemySoldier::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABullet::StaticClass())) {
		OtherActor->Destroy();
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	}

	 
	//GetCharacterMovement()->DisableMovement();
}

void AEnemySoldier::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
		UE_LOG(LogTemp, Warning, TEXT("몽타주가 중단되었습니다!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("몽타주가 정상적으로 끝났습니다!"));
		
	}

}

void AEnemySoldier::Fire()
{
	
	soldier_anim->Fire();

	//soldier_anim->Montage_SetEndDelegate(FOnMontageEnded::CreateUObject(this, &AEnemySoldier::OnMontageEnded), soldier_anim->Fire_Montage);
	
}



