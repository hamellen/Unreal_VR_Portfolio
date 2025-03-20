// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Squad_GameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);
DECLARE_MULTICAST_DELEGATE(FDele_Treasure);
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

	

	void Left_Treasure();

	

	UPROPERTY(EditAnywhere, Category = Count)
	int32 count_Treasure;
	
	FDele_Multi Fuc_DeleMulti;

	FDele_Treasure Fuc_Treasure;
	
	UPROPERTY(VisibleAnywhere,Category=Class_Soldier)
	TSubclassOf<class AEnemySoldier> class_soldier;

	UPROPERTY(VisibleAnywhere,Category=TARGET)
	TArray<AActor*> Target;

	void SpawnSoldier();

	FTimerHandle TimerHandle;

	
};
