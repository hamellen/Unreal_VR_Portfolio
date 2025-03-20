// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFire_BT_TASK.h"
#include "../Monster/EnemySoldier.h"
#include "../Monster/Enemy_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Animation/Soldier_Animinstance.h"
UEnemyFire_BT_TASK::UEnemyFire_BT_TASK()
{
	bNotifyTick = true;
	NodeName = TEXT("Enemy_Fire_Task");
}

EBTNodeResult::Type UEnemyFire_BT_TASK::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	pawn = Cast<AEnemySoldier>(OwnerComp.GetAIOwner()->GetPawn());
	if (!pawn) {
		return EBTNodeResult::Failed;
	}
	FVector location = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("Player_Location"));

	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(pawn->GetActorLocation(), location);
	pawn->SetActorRotation(rotation);
	pawn->Fire();
	
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UEnemyFire_BT_TASK::OnMontageEnded, &OwnerComp);
	pawn->soldier_anim->Montage_SetEndDelegate(EndDelegate, pawn->soldier_anim->Fire_Montage);//적 몽타지 종료시까지의 델리게이트 설정

	return EBTNodeResult::InProgress;  
	

	

}

void UEnemyFire_BT_TASK::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp)
	{
		
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}

}




