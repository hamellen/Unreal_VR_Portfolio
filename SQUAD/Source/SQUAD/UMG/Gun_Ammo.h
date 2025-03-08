// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Gun_Ammo.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SQUAD_API UGun_Ammo : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized();

	UPROPERTY(EditAnywhere,Category=Ammo)
	TObjectPtr<UTextBlock> Ammo;

};
