// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyFire_BT_TASK.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API UEnemyFire_BT_TASK : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UEnemyFire_BT_TASK();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	//virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UPROPERTY(VisibleAnywhere,Category=Player)
	TObjectPtr<class AEnemySoldier> pawn;

	
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp);
	
};
