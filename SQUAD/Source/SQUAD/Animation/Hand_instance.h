// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Hand_instance.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API UHand_instance : public UAnimInstance
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HandIndex)
	float Pose_Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HandIndex)
	float Current_Pose_Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HandIndex)
	float Hand_Speed;

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);


};
