// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySoldier.generated.h"

class UStatComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class AAK_Rifle;
class ABullet;
class USoldier_Animinstance;



UCLASS()
class SQUAD_API AEnemySoldier : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemySoldier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = STAT)
	TObjectPtr<UStatComponent> stat;

	UPROPERTY(EditAnywhere, Category = SKELETAL)
	TArray<TObjectPtr<USkeletalMesh>> sk_array;

	UPROPERTY(VisibleAnywhere,Category=bullet)
	TSubclassOf<class ABullet> bullet_class;

	UPROPERTY(EditAnywhere, Category = Skeletal)
	TObjectPtr<USkeletalMeshComponent> gun_mesh;

	UPROPERTY(VisibleAnywhere,Category=Anim)
	TObjectPtr<USoldier_Animinstance> soldier_anim;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void Fire();

	UPROPERTY(EditAnywhere,Category=Ready)
	bool ReadyToFire;
	
};