// Fill out your copyright notice in the Description page of Project Settings.


#include "Situation_Bar.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Util/Squad_GameMode.h"
void USituation_Bar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_Left_Treasure = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Treasure")));

	Button_Exit= Cast<UButton>(GetWidgetFromName(TEXT("ButtonExit")));

	Button_Exit->OnClicked.AddDynamic(this, &USituation_Bar::End_Game);
	Squad_Mode = Cast<ASquad_GameMode>(GetWorld()->GetAuthGameMode());
	Squad_Mode->Fuc_Treasure.AddUObject(this, &USituation_Bar::SetTextLeftTreasure);

}



void USituation_Bar::End_Game()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningLocalPlayer()->GetPlayerController(GetWorld()), EQuitPreference::Quit, false);

}

void USituation_Bar::SetTextLeftTreasure()
{
	Text_Left_Treasure->Text= FText::Format(FText::FromString("³²Àº Å»Ãë¹°ÀÇ °¹¼ö: {0}"), FText::AsNumber(Squad_Mode->count_Treasure));

}


