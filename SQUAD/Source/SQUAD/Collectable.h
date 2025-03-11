// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

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



};
