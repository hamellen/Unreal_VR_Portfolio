// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Squad_Pawn.generated.h"

class UInputAction;
class UCameraComponent;
class UCapsuleComponent;
class UStatComponent;
struct FInputActionValue;
class UFloatingPawnMovement;
class ASquad_Hand;

UCLASS()
class SQUAD_API ASquad_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASquad_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Horizon;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Vertical;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Left_Grip;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Left_Trigger;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Right_Grip;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Right_Trigger;





	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Capsule)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = Stat)
	TObjectPtr<UStatComponent> Stat;

	UPROPERTY(EditAnywhere, Category = Move)
	TObjectPtr<UFloatingPawnMovement> Pawn_Movement;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = VR)
	TObjectPtr<USceneComponent> Vr_Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	TObjectPtr<USceneComponent> Base_Root;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hand)
	TObjectPtr<ASquad_Hand> Right_Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hand)
	TObjectPtr<ASquad_Hand> Left_Hand;


	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=Height)
	float Desired_height;

	UPROPERTY(EditAnywhere, Category = Speed)
	float Speed;

	UPROPERTY()
	TSubclassOf<ASquad_Hand> hand_class;


	void Left_Grip(const FInputActionValue& Value);
	void Left_Release(const FInputActionValue& Value);
	void Left_Trigger(const FInputActionValue& Value);
	void Right_Grip(const FInputActionValue& Value);
	void Right_Release(const FInputActionValue& Value);
	void Right_Trigger(const FInputActionValue& Value);


	void Move_Horizon(const FInputActionValue& Value);
	void Move_Vertical(const FInputActionValue& Value);

	void Spawn_Hands();

};
