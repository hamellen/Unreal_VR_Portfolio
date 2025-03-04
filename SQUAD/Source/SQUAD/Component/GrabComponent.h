// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameplayTagContainer.h"
#include "GrabComponent.generated.h"

UENUM()
enum class EGrabEnum :uint8
{
	ObjectToHand UMETA(DisplayName = "ObjectToHand"),
	HandToObject UMETA(DisplayName = "HandToObject"),
	Free UMETA(DisplayName = "Free")
};

DECLARE_MULTICAST_DELEGATE(GrabTrigger);

class ASquad_Hand;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SQUAD_API UGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabComponent();

	UPROPERTY(EditAnywhere, Category = Ammo)
	FGameplayTag DefaultGrabType= FGameplayTag::RequestGameplayTag("VR.Object.ObjectToHand");

	UPROPERTY(EditAnywhere, Category = Ammo)
	FGameplayTag ObjectToHand = FGameplayTag::RequestGameplayTag("VR.Object.ObjectToHand");

	UPROPERTY(EditAnywhere, Category = Ammo)
	FGameplayTag HandToObject = FGameplayTag::RequestGameplayTag("VR.Object.HandToObject");


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPhysics(bool bPhysics);

	void Bind(TObjectPtr<ASquad_Hand>  TargetHand);
	void UnBind();
	void TryTrigger();

	UPROPERTY(EditAnywhere,Category=Hand)
	TObjectPtr<ASquad_Hand> OwingHand;

	GrabTrigger grabtrigger;

	UPROPERTY(EditAnywhere)
	EGrabEnum grab_type;


	UPROPERTY(EditAnywhere,Category=bheld)
	bool bheld;

	FRotator InvertRotator(const FRotator& Rotator);
};
