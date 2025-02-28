// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Magazine.generated.h"

UCLASS()
class SQUAD_API AMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagazine();

	UPROPERTY(EditAnywhere,Category=Mesh)
	TObjectPtr<UStaticMeshComponent> Magazine;

	UPROPERTY(EditAnywhere, Category = Ammo)
	int32 ammo;

	UPROPERTY(EditAnywhere, Category = Collision)
	TObjectPtr<class UGrabComponent> GrabComponent;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
