// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStat_Actor.generated.h"

class UUserWidget;
class UWidgetComponent;
class UPlayer_Stat;

UCLASS()
class SQUAD_API APlayerStat_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStat_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = cl_simulation)
	TSubclassOf<UUserWidget> Cl_Stat;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	TObjectPtr<UWidgetComponent> PlayerStat_Component;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	TObjectPtr<UPlayer_Stat> Player_Stat;

	UPROPERTY(VisibleAnywhere, Category = CameraManager)
	TObjectPtr<class APlayerCameraManager> CameraManager;

	
	UPROPERTY(EditAnywhere, Category = Value)
	float index_foward;

	UPROPERTY(EditAnywhere, Category = Value)
	float index_up;


	UPROPERTY(EditAnywhere, Category = Value)
	float index_right;
};
