// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rifle.h"
#include "AK_Rifle.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API AAK_Rifle : public ARifle
{
	GENERATED_BODY()
	
public:

	AAK_Rifle();

	UPROPERTY(EditAnywhere, Category = Damage)
	float fire_interval;

	UPROPERTY(EditAnywhere, Category = Collision)
	TObjectPtr<class UBoxComponent> Magazine_box;

	UPROPERTY(EditAnywhere, Category = Collision)
	TObjectPtr<class UGrabComponent> GrabComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Weapon_Fire();
	virtual void Reload_Ammo();
};
