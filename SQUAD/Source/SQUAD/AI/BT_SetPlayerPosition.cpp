// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_SetPlayerPosition.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/Squad_Pawn.h"
#include "BehaviorTree/BlackboardComponent.h"
UBT_SetPlayerPosition::UBT_SetPlayerPosition()
{

	NodeName = TEXT("SetPlayerPosition_V2");
}

void UBT_SetPlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto pawn=Cast<ASquad_Pawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquad_Pawn::StaticClass()));
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Player_Location"), pawn->GetActorLocation());//몇초마다 플레이어의 위치 설정

}
