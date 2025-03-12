// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Set_PlayerPostion_BTService.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API USet_PlayerPostion_BTService : public UBTService
{
	GENERATED_BODY()
	
public:

	USet_PlayerPostion_BTService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UPROPERTY(EditAnywhere,Category=BlackBoard)
	FBlackboardKeySelector BlackBoardKey;

	

};
