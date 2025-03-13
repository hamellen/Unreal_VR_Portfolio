// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Squad_GameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

class UAudioComponent;
/**
 * 
 */
UCLASS()
class SQUAD_API ASquad_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ASquad_GameMode();

	virtual void BeginPlay() override;

	void DecreaseSoldier();

	UPROPERTY(EditAnywhere,Category=Count)
	int32 count_soldier;

	UPROPERTY(EditAnywhere, Category = Count)
	int32 max_count_soldier;

	
	FDele_Multi Fuc_DeleMulti;
	
};
