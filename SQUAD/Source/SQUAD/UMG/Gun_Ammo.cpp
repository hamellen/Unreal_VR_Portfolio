// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun_Ammo.h"
#include "Components/TextBlock.h"
void UGun_Ammo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Ammo = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Ammo")));

}
