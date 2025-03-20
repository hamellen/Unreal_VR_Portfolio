// Fill out your copyright notice in the Description page of Project Settings.


#include "Last_Menu_Actor.h"
#include "Components/WidgetComponent.h"
#include "Last_Menu.h"
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
ALast_Menu_Actor::ALast_Menu_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>Cl_Last (TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/Last_Menu.Last_Menu_C'"));

	Last_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_Component"));

	if (Cl_Last.Succeeded()) {

		Cl_Last_Menu = Cl_Last.Class;
		Last_Component->SetWidgetClass(Cl_Last_Menu);
		Last_Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Last_Component->SetWidgetSpace(EWidgetSpace::World);
		Last_Component->SetDrawSize(FVector2D(200.f, 200.f));
	}

	UI_Ray = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Component"));

}

// Called when the game starts or when spawned
void ALast_Menu_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	SetWidgetInteractionComponent();

	Last_Object = Cast<ULast_Menu>(Last_Component->GetWidget());

	



	
}

// Called every frame
void ALast_Menu_Actor::Tick(float DeltaTime)
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

void ALast_Menu_Actor::SetWidgetInteractionComponent()
{
	auto pawn = Cast<ASquad_Pawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (pawn) {

		WidgetInteraction = pawn->Right_Hand->WidgetInteraction;
	}
	else if (!pawn) {

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("No Pawn"));
	}


}

void ALast_Menu_Actor::Last_Time_Text()
{
	

}



