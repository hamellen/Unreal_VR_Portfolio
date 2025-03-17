// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Last_Menu.generated.h"


class UButton;
class  UTextBlock;
class ASquad_GameMode;
/**
 * 
 */
UCLASS()
class SQUAD_API ULast_Menu : public UUserWidget
{
	GENERATED_BODY()
	
public:


	virtual void NativeOnInitialized();

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, Category = Exit)
	TObjectPtr<UButton> Exit_Button;

	UPROPERTY(VisibleAnywhere, Category = Exit)
	TObjectPtr<UTextBlock> Time_Text;

	UPROPERTY(VisibleAnywhere, Category = GameMode)
	TObjectPtr<ASquad_GameMode> game_mode;


	UFUNCTION(BlueprintCallable)
	void QuitGame();

};
