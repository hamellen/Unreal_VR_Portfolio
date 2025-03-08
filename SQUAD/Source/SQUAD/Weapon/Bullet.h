// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UCapsuleComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;

UCLASS()
class SQUAD_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category=Collision)
	TObjectPtr<UCapsuleComponent> CapsuleCollision;

	UPROPERTY(EditAnywhere, Category = Niagara)
	TObjectPtr<UNiagaraSystem> NiagaraSystem;
	
	UPROPERTY(VisibleAnywhere,Category=Niagara)
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	TObjectPtr<UProjectileMovementComponent> Projectile;

};
