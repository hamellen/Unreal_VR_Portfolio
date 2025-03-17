// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStat_Actor.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../UMG/Player_Stat.h"
// Sets default values
APlayerStat_Actor::APlayerStat_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>Cl_STAT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/HP_Bar.HP_Bar_C'"));

	PlayerStat_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_Component"));

	if (Cl_STAT.Succeeded()) {

		Cl_Stat = Cl_STAT.Class;
		PlayerStat_Component->SetWidgetClass(Cl_Stat);
		PlayerStat_Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayerStat_Component->SetWidgetSpace(EWidgetSpace::World);
		PlayerStat_Component->SetDrawSize(FVector2D(100.f, 100.f));
	}


}

// Called when the game starts or when spawned
void APlayerStat_Actor::BeginPlay()
{
	Super::BeginPlay();
	

	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	Player_Stat = Cast<UPlayer_Stat>(PlayerStat_Component->GetWidget());
}

// Called every frame
void APlayerStat_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Camera_Location = CameraManager->GetCameraLocation();
	FRotator Camera_Rotation = CameraManager->GetCameraRotation();
	FRotator YawRoation(0, Camera_Rotation.Yaw, 0);

	FVector ForwardDirection = FRotationMatrix(YawRoation).GetUnitAxis(EAxis::X);
	FVector UpDirection = FRotationMatrix(YawRoation).GetUnitAxis(EAxis::Z);
	FVector RightDirection = FRotationMatrix(YawRoation).GetUnitAxis(EAxis::Y);

	SetActorLocation(Camera_Location + index_foward * ForwardDirection + index_up * UpDirection+ index_right* RightDirection);

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Camera_Location));
}

