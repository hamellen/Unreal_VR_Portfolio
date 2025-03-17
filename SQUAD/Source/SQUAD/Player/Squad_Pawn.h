// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Squad_Pawn.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_Multi);

class UInputAction;
class UCameraComponent;
class UCapsuleComponent;
class UStatComponent;
struct FInputActionValue;
class UFloatingPawnMovement;
class ASquad_Hand;
class UAIPerceptionStimuliSourceComponent;
class ASimulation_Actor;
class APlayerStat_Actor;
class UWidgetComponent;
class ALast_Menu_Actor;
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

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Menu;



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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Root)
	TObjectPtr<USceneComponent> Base_Component;

	UPROPERTY(EditAnywhere, Category = Sensing)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> Sensing_Component;
	

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

	UPROPERTY()
	TSubclassOf<ASimulation_Actor> Menu_class;

	

	UPROPERTY()
	TObjectPtr<ASimulation_Actor> Menu_Object;

	UPROPERTY(VisibleAnywhere,Category=Class_PlayerStat)
	TSubclassOf<APlayerStat_Actor> class_stat;

	UPROPERTY(VisibleAnywhere, Category = PlayerStat)
	TObjectPtr< APlayerStat_Actor> PlayerStat_actor;


	UPROPERTY(EditAnywhere,Category=Goal)
	int32 current_number_goal;

	UPROPERTY(EditAnywhere, Category = Goal)
	int32 max_number_goal;

	UPROPERTY()
	TSubclassOf<ALast_Menu_Actor> Last_class;

	void Left_Grip(const FInputActionValue& Value);
	void Left_Release(const FInputActionValue& Value);
	void Left_Trigger(const FInputActionValue& Value);
	void Right_Grip(const FInputActionValue& Value);
	void Right_Release(const FInputActionValue& Value);
	void Right_Trigger(const FInputActionValue& Value);


	void Move_Horizon(const FInputActionValue& Value);
	void Move_Vertical(const FInputActionValue& Value);

	void Spawn_Hands();

	void Spawn_Menu(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere,Category=GameMode)
	TObjectPtr<class ASquad_GameMode> game_mode;

	void Spawn_Last_Menu();


	FDele_Multi Fuc_DeleMulti;//bullet hited
};
