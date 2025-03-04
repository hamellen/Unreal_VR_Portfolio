// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Squad_Hand.generated.h"

class UMotionControllerComponent;
class USkeletalMeshComponent;
class UHand_instance;
class UGrabComponent;
UCLASS()
class SQUAD_API ASquad_Hand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquad_Hand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Hand)
	TObjectPtr<UMotionControllerComponent> motioncontroller;

	UPROPERTY(EditAnywhere, Category = Hand)
	TObjectPtr<USkeletalMeshComponent> hand_mesh;

	UPROPERTY(EditAnywhere, Category = Scene)
	TObjectPtr<USceneComponent> scene_object;

	UPROPERTY(EditAnywhere,Category=Tag)
	FGameplayTag hand_tag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, Category = Radius)
	float secsing_rad;

	void Grab();

	void Release();

	void Trigger();
	
	UPROPERTY(VisibleAnywhere,Category=HandAnim)
	TObjectPtr<UHand_instance> hand_instance;
	
	UPROPERTY(VisibleAnywhere,Category=Grab)
	TObjectPtr<UGrabComponent> GrabCom;

	


	
	UGrabComponent* FindGrabComponent();
	
};
