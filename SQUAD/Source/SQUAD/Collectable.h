// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

class ASquad_GameMode;

UCLASS()
class SQUAD_API ACollectable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Mesh;


	UPROPERTY(EditAnywhere, Category = Mesh_Array)
	TArray<TObjectPtr<UStaticMesh>> Mesh_Array;

	UPROPERTY(VisibleAnywhere, Category = GameMode)
	TObjectPtr<ASquad_GameMode> Squad_Game_Object;


	void NotifyHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);

};
