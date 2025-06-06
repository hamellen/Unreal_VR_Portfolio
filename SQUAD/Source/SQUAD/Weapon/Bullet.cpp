// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include  "../Util/SquadGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(CapsuleCollision);


	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	Projectile->InitialSpeed = 5000.f;
	Projectile->MaxSpeed = 5000.f;
	Projectile->bAutoActivate = true;
	Projectile->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	Projectile->Velocity = CapsuleCollision->GetForwardVector() * Projectile->InitialSpeed;
	NiagaraSystem = *Cast<USquadGameInstance>(GetWorld()->GetGameInstance())->Map_Vfx.Find("Bullet_Vfx");

	
	NiagaraComponent->SetAsset(NiagaraSystem);
	NiagaraComponent->Activate(true);
	SetLifeSpan(5.0f);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::NotifyHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	Destroy();
}

