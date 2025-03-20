// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BT_SetPlayerPosition.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API UBT_SetPlayerPosition : public UBTService
{
	GENERATED_BODY()
	
public:

	UBT_SetPlayerPosition();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
