// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SquadPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class SQUAD_API ASquadPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


public:


	UPROPERTY(EditAnywhere,Category=Mapping)
	TObjectPtr<UInputMappingContext> Vr_Mapping;


};
