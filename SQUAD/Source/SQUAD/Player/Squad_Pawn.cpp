﻿ // Fill out your copyright notice in the Description page of Project Settings.


#include "Squad_Pawn.h"
#include "Components/CapsuleComponent.h"
#include "../Component/StatComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Squad_Hand.h"
#include "Kismet/GameplayStatics.h"
#include "../Util/SquadGameInstance.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "../UMG/Simulation_Actor.h"
#include "../Util/Squad_GameMode.h"
#include "../UMG/Situation_Bar.h"
#include"../UMG/PlayerStat_Actor.h"
#include "../UMG/Last_Menu_Actor.h"
#include "../Weapon/Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
// Sets default values
ASquad_Pawn::ASquad_Pawn()
{
	static ConstructorHelpers::FClassFinder<ASquad_Hand>Hand_c(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_MySquad_Hand.BP_MySquad_Hand_C'"));
	
	static ConstructorHelpers::FClassFinder<ASimulation_Actor>Menu_c(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Simulation_Actor.BP_Simulation_Actor_C'"));

	static ConstructorHelpers::FClassFinder<APlayerStat_Actor>PlayerStat_c(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_PlayerStat_Actor.BP_PlayerStat_Actor_C'"));

	static ConstructorHelpers::FClassFinder<ALast_Menu_Actor>Last_c(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Last_Menu_Actor.BP_Last_Menu_Actor_C'"));

	if (Hand_c.Succeeded()) {
	
		hand_class = Hand_c.Class;
	}

	if (Menu_c.Succeeded()) {
		Menu_class = Menu_c.Class;
	}

	if (PlayerStat_c.Succeeded()) {
	
		class_stat = PlayerStat_c.Class;
	}

	if (Last_c.Succeeded()) {
		Last_class = Last_c.Class;
	}
	

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Base_Component=CreateDefaultSubobject<USceneComponent>(TEXT("Base_Root"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(Base_Component);

	Vr_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Vr_Root"));
	Vr_Root->SetupAttachment(Base_Component);

	
	Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Vr_Root);


	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
	Pawn_Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	Sensing_Component = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AI_Stimulate"));
	Sensing_Component->RegisterWithPerceptionSystem();

	
}

// Called when the game starts or when spawned
void ASquad_Pawn::BeginPlay()
{
	Super::BeginPlay();
	game_mode = Cast<ASquad_GameMode>(GetWorld()->GetAuthGameMode());
	
	CapsuleComponent->OnComponentHit.AddDynamic(this, &ASquad_Pawn::OnHit);
	Spawn_Hands();
	Squad_Instance = Cast<USquadGameInstance>(GetWorld()->GetGameInstance());
	
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





	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr)
	{
		Input->BindAction(IA_Horizon, ETriggerEvent::Triggered, this, &ASquad_Pawn::Move_Horizon);
		Input->BindAction(IA_Vertical, ETriggerEvent::Triggered, this, &ASquad_Pawn::Move_Vertical);

		Input->BindAction(IA_Left_Grip, ETriggerEvent::Started, this, &ASquad_Pawn::Left_Grip);
		Input->BindAction(IA_Left_Grip, ETriggerEvent::Completed, this, &ASquad_Pawn::Left_Release);
		Input->BindAction(IA_Left_Trigger, ETriggerEvent::Started, this, &ASquad_Pawn::Left_Trigger);

		Input->BindAction(IA_Right_Grip, ETriggerEvent::Started, this, &ASquad_Pawn::Right_Grip);
		Input->BindAction(IA_Right_Grip, ETriggerEvent::Completed, this, &ASquad_Pawn::Right_Release);
		Input->BindAction(IA_Right_Trigger, ETriggerEvent::Started, this, &ThisClass::Right_Trigger);
		
		Input->BindAction(IA_Menu, ETriggerEvent::Started, this, &ThisClass::Spawn_Menu);

		
	}

}

void ASquad_Pawn::Left_Grip(const FInputActionValue& Value)
{
	
	Left_Hand->Grab();

}

void ASquad_Pawn::Left_Release(const FInputActionValue& Value)
{
	Left_Hand->Release();

}

void ASquad_Pawn::Left_Trigger(const FInputActionValue& Value)
{

	Left_Hand->Trigger();
}

void ASquad_Pawn::Right_Grip(const FInputActionValue& Value)
{
	Right_Hand->Grab();
}

void ASquad_Pawn::Right_Release(const FInputActionValue& Value)
{
	Right_Hand->Release();

}

void ASquad_Pawn::Right_Trigger(const FInputActionValue& Value)
{

	Right_Hand->Trigger();
}

void ASquad_Pawn::Move_Horizon(const FInputActionValue& Value)
{
	

	float value = Value.Get<float>();
	if (Controller != nullptr)
	{
		
			// find out which way is forward
			const FRotator Rotation = Camera->GetComponentRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
	
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
			AddMovementInput(RightDirection, value * Speed);
	}

}

void ASquad_Pawn::Move_Vertical(const FInputActionValue& Value)
{
	float value = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Camera->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);


		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, value*Speed);

		
	}
}



void ASquad_Pawn::Spawn_Hands()
{

	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;


	Left_Hand = GetWorld()->SpawnActor<ASquad_Hand>(hand_class, GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
	Left_Hand->AttachToComponent(Vr_Root, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	Left_Hand->hand_tag = FGameplayTag::RequestGameplayTag("VR.HAND.LEFT");
	Left_Hand->hand_mesh->SetRelativeRotation(FRotator(0, 0, 90));
	Left_Hand->hand_mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, -1.0f));
	Left_Hand->motioncontroller->SetTrackingMotionSource(FName("Left"));

	Right_Hand = GetWorld()->SpawnActor<ASquad_Hand>(hand_class, GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
	Right_Hand->AttachToComponent(Vr_Root, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	Right_Hand->hand_tag = FGameplayTag::RequestGameplayTag("VR.HAND.RIGHT");
	Right_Hand->hand_mesh->SetRelativeRotation(FRotator(0, 0, 90));
	Right_Hand->motioncontroller->SetTrackingMotionSource(FName("Right"));

}

void ASquad_Pawn::Spawn_Menu(const FInputActionValue& Value)
{
	if (!Menu_Object) {
	
		Menu_Object = GetWorld()->SpawnActor<ASimulation_Actor>(Menu_class, Camera->GetComponentLocation(), Camera->GetComponentRotation());
		PlayerStat_actor = GetWorld()->SpawnActor<APlayerStat_Actor>(class_stat, Camera->GetComponentLocation(), Camera->GetComponentRotation());
	}
	else if (Menu_Object) {
	
		Menu_Object->CloseMenu();
		Menu_Object = nullptr;

		PlayerStat_actor->Destroy();
		PlayerStat_actor = nullptr;
	}
	
}

void ASquad_Pawn::Spawn_Last_Menu()//모든 오브젝트 수집후 엔딩존 진입
{
	auto last=GetWorld()->SpawnActor<ALast_Menu_Actor>(Last_class, Camera->GetComponentLocation(), Camera->GetComponentRotation());
	
	
}

void ASquad_Pawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor->IsA(ABullet::StaticClass())) {
	
		
		UGameplayStatics::PlaySoundAtLocation(this, *Squad_Instance->Map_Cue.Find(TEXT("Hited_sfx")), GetActorLocation());
		Stat->Current_Hp -= 5;
		Fuc_DeleMulti.Broadcast();
	}

}

