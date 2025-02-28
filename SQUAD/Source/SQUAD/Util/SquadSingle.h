// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SquadSingle.generated.h"

/**
 * 
 */
UCLASS()
class SQUAD_API USquadSingle : public UObject
{
	GENERATED_BODY()
	
public:


	USquadSingle();
	static USquadSingle& GetSingle();
};
