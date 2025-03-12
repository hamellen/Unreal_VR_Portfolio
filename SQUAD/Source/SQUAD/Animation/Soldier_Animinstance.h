// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Soldier_Animinstance.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API USoldier_Animinstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	void NativeInitializeAnimation();
	void NativeUpdateAnimation(float DeltaSeconds);


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=SPEED)
	float move_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ready)
	bool ReadyToFire;

	UPROPERTY(EditAnywhere,Category=SOLDIER)
	TObjectPtr<class AEnemySoldier> enemy;


	UPROPERTY(EditAnywhere, Category = Montage)
	TObjectPtr<UAnimMontage> Fire_Montage;

	

	UFUNCTION()
	void AnimNotify_bullet_fire();

	void Fire();
};
