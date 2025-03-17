// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Stat.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "../Player/Squad_Pawn.h"
#include "../Component/StatComponent.h"
void UPlayer_Stat::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Weapon_image = Cast<UImage>(GetWidgetFromName(TEXT("Weapon_img")));

	ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_ProgressBar")));

}

void UPlayer_Stat::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<ASquad_Pawn>(GetOwningPlayerPawn());

	Weapon_image->SetRenderOpacity(0.0f);

	ProgressBar->SetPercent((float)player->Stat->Current_Hp / (float)player->Stat->Max_Hp);

}

void UPlayer_Stat::StatEvent()
{

	ProgressBar->SetPercent((float)player->Stat->Current_Hp / (float)player->Stat->Max_Hp);

}

void UPlayer_Stat::SwitchImage()
{
	if (bImage) {
	
		Weapon_image->SetRenderOpacity(0.0f);
		
	}
	else if (!bImage) {
	
		Weapon_image->SetRenderOpacity(1.0f);
	}
	bImage = !bImage;
}


