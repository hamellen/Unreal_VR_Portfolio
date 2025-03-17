// Fill out your copyright notice in the Description page of Project Settings.


#include "Set_PlayerPostion_BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Player/Squad_Pawn.h"
USet_PlayerPostion_BTService::USet_PlayerPostion_BTService()
{
	Interval = 0.5f;
	NodeName = TEXT("SetPlayerPosition");
}

void USet_PlayerPostion_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto pawn = Cast<ASquad_Pawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Player_Location"), pawn->GetActorLocation());//몇초마다 플레이어의 위치 설정
}
