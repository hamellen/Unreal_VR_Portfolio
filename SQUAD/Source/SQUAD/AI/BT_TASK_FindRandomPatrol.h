// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_TASK_FindRandomPatrol.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API UBT_TASK_FindRandomPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBT_TASK_FindRandomPatrol();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
	UPROPERTY(VisibleAnywhere,Category=Pawn)
	TObjectPtr<class AEnemySoldier> pawn;

	UPROPERTY(EditAnywhere,Category=Radius)
	float searching_radius;
};
