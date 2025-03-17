// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player_Stat.generated.h"


class UImage;
class UProgressBar;
class ASquad_Pawn;
/**
 * 
 */
UCLASS()
class SQUAD_API UPlayer_Stat : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized();

	virtual void NativeConstruct() override;


	UPROPERTY(VisibleAnywhere,Category=image)
	TObjectPtr<UImage> Weapon_image;

	UPROPERTY(VisibleAnywhere, Category = ProgressBar)
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(EditAnywhere,Category=Image_Map)
	TArray<TObjectPtr<UTexture2D>> array_image;

	UPROPERTY(VisibleAnywhere,Category=Player)
	TObjectPtr<ASquad_Pawn> player;

	void StatEvent();

	void SwitchImage();

	UPROPERTY(VisibleAnywhere)
	bool bImage=false;
};
