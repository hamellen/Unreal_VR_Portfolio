// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad_Pawn.h"
#include "Components/CapsuleComponent.h"
#include "../Component/StatComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "InputActionValue.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Squad_Hand.h"


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
	
	
	




	Spawn_Hands();
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
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASquad_Pawn::Move);
		Input->BindAction(IA_Left_Grip, ETriggerEvent::Started, this, &ASquad_Pawn::Left_Grip);
		Input->BindAction(IA_Left_Trigger, ETriggerEvent::Started, this, &ASquad_Pawn::Left_Trigger);
		Input->BindAction(IA_Right_Grip, ETriggerEvent::Triggered, this, &ASquad_Pawn::Right_Grip);
		
		Input->BindAction(IA_Right_Trigger, ETriggerEvent::Triggered, this, &ThisClass::Right_Trigger);
		Input->BindAction(IA_Right_Trigger, ETriggerEvent::Started, this, &ThisClass::Right_Trigger);
		Input->BindAction(IA_Right_Trigger, ETriggerEvent::Ongoing, this, &ThisClass::Right_Trigger);
		Input->BindAction(IA_Right_Trigger, ETriggerEvent::Completed, this, &ThisClass::Right_Trigger);


		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Setup Complete"));
	}

}

void ASquad_Pawn::Left_Grip(const FInputActionValue& Value)
{

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left_Grip"));
	UE_LOG(LogTemp, Warning, TEXT("Left_Grip"));

}

void ASquad_Pawn::Left_Trigger(const FInputActionValue& Value)
{

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left_Trigger"));
	UE_LOG(LogTemp, Warning, TEXT("Left_Trigger"));
}

void ASquad_Pawn::Right_Grip(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right_Grip"));
	UE_LOG(LogTemp, Warning, TEXT("Right_Grip"));
}

void ASquad_Pawn::Right_Trigger(const FInputActionValue& Value)
{

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right_Trigger"));
	UE_LOG(LogTemp, Warning, TEXT("Right_Trigger"));
}

void ASquad_Pawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Move Detected"));

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);

		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void ASquad_Pawn::Spawn_Hands()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;


	Left_Hand = GetWorld()->SpawnActor<ASquad_Hand>(ASquad_Hand::StaticClass(), GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
	Left_Hand->AttachToComponent(Vr_Root, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	Left_Hand->hand_tag = FGameplayTag::RequestGameplayTag("VR.HAND.LEFT");
	Left_Hand->hand_mesh->SetRelativeRotation(FRotator(0, 0, 90));
	Left_Hand->hand_mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, -1.0f));
	Left_Hand->motioncontroller->SetTrackingMotionSource(FName("Left"));

	Right_Hand = GetWorld()->SpawnActor<ASquad_Hand>(ASquad_Hand::StaticClass(), GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
	Right_Hand->AttachToComponent(Vr_Root, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	Right_Hand->hand_tag = FGameplayTag::RequestGameplayTag("VR.HAND.RIGHT");
	Right_Hand->hand_mesh->SetRelativeRotation(FRotator(0, 0, 90));
	Right_Hand->motioncontroller->SetTrackingMotionSource(FName("Right"));

}

