// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SirenHeader.generated.h"

class ASquad_GameMode;

UCLASS()
class SQUAD_API ASirenHeader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASirenHeader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,Category=GameMode)
	TObjectPtr<ASquad_GameMode> GameMode_Squad;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> Siren_Mesh;


	UPROPERTY(VisibleAnywhere, Category = Scene)
	TObjectPtr<USceneComponent> sound_location;

	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<class USoundBase> Siren_cue;

	UPROPERTY(EditAnywhere, Category = audio)
	float index_sound;

	void Play_Siren();
};
