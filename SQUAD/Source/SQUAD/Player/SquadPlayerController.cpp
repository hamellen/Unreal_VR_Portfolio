// Fill out your copyright notice in the Description page of Project Settings.


#include "SquadPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ASquadPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(Vr_Mapping, 0);
	}

}

void ASquadPlayerController::SetupInputComponent()
{

	Super::SetupInputComponent();


}
