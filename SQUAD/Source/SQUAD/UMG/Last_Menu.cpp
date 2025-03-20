// Fill out your copyright notice in the Description page of Project Settings.


#include "Last_Menu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Util/Squad_GameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
void ULast_Menu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Time_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("Ttext")));

	Exit_Button = Cast<UButton>(GetWidgetFromName(TEXT("Ebutton")));
}

void ULast_Menu::NativeConstruct()
{
	Super::NativeConstruct();

	game_mode = Cast<ASquad_GameMode>(GetWorld()->GetAuthGameMode());

	
}

void ULast_Menu::QuitGame()
{
	if (GetWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}

}


