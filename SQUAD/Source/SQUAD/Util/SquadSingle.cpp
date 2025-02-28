// Fill out your copyright notice in the Description page of Project Settings.


#include "SquadSingle.h"

USquadSingle::USquadSingle()
{
}

USquadSingle& USquadSingle::GetSingle()
{
	USquadSingle* single = Cast<USquadSingle>(GEngine->GameSingleton);
	if (single) {
		return *single;
	}


	return *NewObject<USquadSingle>();
	
}
