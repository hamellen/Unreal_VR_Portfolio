// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_Controller.generated.h"


class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class SQUAD_API AEnemy_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemy_Controller();

	virtual void OnPossess(APawn* InPawn);

	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<UAIPerceptionComponent> AI_Perception;

	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<UAISenseConfig_Sight> AI_Sight;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere, Category=Pawn)
	TObjectPtr<class AEnemySoldier> soldier;

};
