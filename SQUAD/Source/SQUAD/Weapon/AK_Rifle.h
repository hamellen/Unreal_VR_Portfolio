// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rifle.h"
#include "AK_Rifle.generated.h"

class URifle_Animinstance;
class USquadGameInstance;
class UWidgetComponent;
class UGun_Ammo;
class UUserWidget;
class ABullet;
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

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<class URifle_Animinstance> Gun_Animinstance;
	
	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<class USquadGameInstance> Squad_Instance;

	UPROPERTY(EditAnywhere, Category = Grip)
	TObjectPtr<class UBoxComponent> GripBox;


	UPROPERTY(EditAnywhere,Category=Magazine)
	TObjectPtr<class AMagazine> Magazine_Object;


	UPROPERTY(EditAnywhere, Category = Magazine_Vector)
	FVector  Magazine_Position;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Weapon_Fire();
	virtual void Reload_Ammo();

	UPROPERTY(EditAnywhere, Category = UMG)
	TObjectPtr<UWidgetComponent> Widget_Ammo;

	UPROPERTY(EditAnywhere, Category = UMG)
	TSubclassOf<UUserWidget> Ammo_UMG_Class;

	UPROPERTY(EditAnywhere,Category=UMG)
	TObjectPtr<UGun_Ammo> Ammo_UMG;

	UPROPERTY(EditAnywhere, Category = Bullet)
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(EditAnywhere, Category = Hand)
	TObjectPtr<class ASquad_Hand> Vertical_Left;


	


	UFUNCTION()
	void OnOverlapHandBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndHandOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
