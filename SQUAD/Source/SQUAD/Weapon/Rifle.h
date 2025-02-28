// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"


UCLASS(Abstract)
class SQUAD_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> main_part;

	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> grip;

	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> magazine;

	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> scope;


	UPROPERTY(EditAnywhere,Category= Ammo)
	int32 current_ammo;

	UPROPERTY(EditAnywhere, Category = Ammo)
	int32 max_ammo;

	UPROPERTY(EditAnywhere, Category = Damage)
	float damage;

	UPROPERTY(EditAnywhere)
	FName grip_socket;

	UPROPERTY(EditAnywhere)
	FName magazine_socket;

	UPROPERTY(EditAnywhere)
	FName scope_socket;

	UPROPERTY(EditAnywhere)
	FName muzzle_socket;

	

	

public:

	virtual void Weapon_Fire();
	virtual void Reload_Ammo();
};
