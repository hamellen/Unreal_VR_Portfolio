// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_TASK_FindRandomPatrol.h"
#include "../Monster/EnemySoldier.h"
#include "../Monster/Enemy_Controller.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
UBT_TASK_FindRandomPatrol::UBT_TASK_FindRandomPatrol()
{
	NodeName = TEXT("Enemy_Random_Position");
}

EBTNodeResult::Type UBT_TASK_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	pawn = Cast<AEnemySoldier>(OwnerComp.GetAIOwner()->GetPawn());

	if (!pawn) {
	
		return EBTNodeResult::Failed;
	
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(pawn->GetWorld());
	if (!NavSystem) {
		return EBTNodeResult::Failed;
	}

	FNavLocation NextPatrol;

	if (NavSystem->GetRandomPointInNavigableRadius(pawn->GetActorLocation(), searching_radius, NextPatrol)) {
	
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Move_To"), NextPatrol);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
