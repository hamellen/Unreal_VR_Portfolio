﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Simulation_Actor.h"
#include "Components/WidgetComponent.h"
#include "Situation_Bar.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/WidgetInteractionComponent.h"
#include "../Player/Squad_Pawn.h"
#include "../Player/Squad_Hand.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASimulation_Actor::ASimulation_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>Cl_Simul(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/Simulatin_Bar.Simulatin_Bar_C'"));

	Simul_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_Component"));

	if (Cl_Simul.Succeeded()) {
	
		Cl_Simulation = Cl_Simul.Class;
		Simul_Component->SetWidgetClass(Cl_Simulation);
		Simul_Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Simul_Component->SetWidgetSpace(EWidgetSpace::World);
		Simul_Component->SetDrawSize(FVector2D(200.f, 200.f));
	}

	UI_Ray= CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Component"));
}

// Called when the game starts or when spawned
void ASimulation_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	Simul_Object = Cast<USituation_Bar>(Simul_Component->GetWidget());

	Simul_Object->SetTextLeftTreasure();

	

	CameraManager=UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	SetWidgetInteractionComponent();
}

// Called every frame
void ASimulation_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Camera_Location = CameraManager->GetCameraLocation();
	FRotator Camera_Rotation = CameraManager->GetCameraRotation();
	FRotator YawRoation(0, Camera_Rotation.Yaw, 0);

	FVector ForwardDirection = FRotationMatrix(YawRoation).GetUnitAxis(EAxis::X);
	FVector UpDirection = FRotationMatrix(YawRoation).GetUnitAxis(EAxis::Z);

	SetActorLocation(Camera_Location + index_foward * ForwardDirection + index_up * UpDirection);

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Camera_Location));

	
}

void ASimulation_Actor::SetWidgetInteractionComponent()
{
	//auto GameMode = Cast<ASquad_GameMode>(GetWorld()->GetAuthGameMode());
	auto pawn = Cast<ASquad_Pawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (pawn) {
	
		WidgetInteraction = pawn->Right_Hand->WidgetInteraction;
	}
	else if (!pawn) {
	
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("No Pawn"));
	}

	

}

void ASimulation_Actor::CloseMenu()
{
	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetWorld()->GetFirstLocalPlayerFromController()))
	{
		Subsystem->RemoveMappingContext(Menu_Mapping);
		Destroy();
	}


}

