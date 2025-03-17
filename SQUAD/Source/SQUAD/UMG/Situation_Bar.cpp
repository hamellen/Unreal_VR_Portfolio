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

	

	
	Squad_Mode = Cast<ASquad_GameMode>(GetWorld()->GetAuthGameMode());
	Squad_Mode->Fuc_Treasure.AddUObject(this, &USituation_Bar::SetTextLeftTreasure);

}

void USituation_Bar::NativeConstruct()
{
	Super::NativeConstruct();

	


	SetTextLeftTreasure();

	

	

}


void USituation_Bar::SetTextLeftTreasure()
{
	FString ScoreString = FString::Printf(TEXT("남은 탈취물의 갯수: %d"), Squad_Mode->count_Treasure);
	Text_Left_Treasure->SetText(FText::FromString(ScoreString));
	
}




