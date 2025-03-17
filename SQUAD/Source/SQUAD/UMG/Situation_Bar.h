// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Situation_Bar.generated.h"


class UTextBlock;
class UButton;
class ASquad_GameMode;
/**
 * 
 */
UCLASS()
class SQUAD_API USituation_Bar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized();

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category = Text)
	TObjectPtr<UTextBlock> Text_Left_Treasure;


	UPROPERTY(EditAnywhere, Category = GameMode)
	TObjectPtr<ASquad_GameMode> Squad_Mode;

	void SetTextLeftTreasure();

	

	
};
