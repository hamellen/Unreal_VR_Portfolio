// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad_Pawn.h"
#include "Components/CapsuleComponent.h"
#include "../Component/StatComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "InputActionValue.h"
// Sets default values
ASquad_Pawn::ASquad_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Base_Root= CreateDefaultSubobject<USceneComponent>(TEXT("Base"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(Base_Root);

	Vr_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Vr_Root"));
	Vr_Root->SetupAttachment(Base_Root);

	
	Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Vr_Root);


	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
	Pawn_Movement = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("PawnMovement"));
}

// Called when the game starts or when spawned
void ASquad_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
	

}

// Called every frame
void ASquad_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASquad_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

