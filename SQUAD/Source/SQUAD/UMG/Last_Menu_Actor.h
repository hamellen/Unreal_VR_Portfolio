// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Last_Menu_Actor.generated.h"

class UUserWidget;
class UWidgetComponent;
class ULast_Menu;
class UNiagaraComponent;


UCLASS()
class SQUAD_API ALast_Menu_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALast_Menu_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, Category = cl_last_menu)
	TSubclassOf<UUserWidget> Cl_Last_Menu;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	TObjectPtr<UWidgetComponent> Last_Component;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	TObjectPtr<ULast_Menu> Last_Object;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NiagaraSystem)
	TObjectPtr<UNiagaraComponent> UI_Ray;

	UPROPERTY(EditAnywhere, Category = Mapping)
	TObjectPtr<class UInputMappingContext> Menu_Mapping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget)
	TObjectPtr<class UWidgetInteractionComponent> WidgetInteraction;

	UPROPERTY(VisibleAnywhere, Category = CameraManager)
	TObjectPtr<class APlayerCameraManager> CameraManager;


	UPROPERTY(EditAnywhere, Category = Value)
	float index_foward;

	UPROPERTY(EditAnywhere, Category = Value)
	float index_up;

	void SetWidgetInteractionComponent();

	void Last_Time_Text();

	
};
