// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include	<xdevapi.h>
#include "SquadGameInstance.generated.h"

class UNiagaraSystem;
class USoundCue;
class UAnimMontage;
/**
 * 
 */
UCLASS()
class SQUAD_API USquadGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	virtual void Init() override;


	//mysqlx::Session* m_Session;
	//mysqlx::Schema* m_SchemaDB;

public:
	USquadGameInstance();
		
	~USquadGameInstance();

public:

	

	/*void ConnectToDataBase(const FString& host, int32 port, const FString& username, const FString& password, const FString& schema);

	

	void CloseDatabaseConnection();*/

	
	UPROPERTY(EditAnywhere, Category = SFX)
	TMap<FString, TObjectPtr<USoundCue>>  Map_Cue;

	UPROPERTY(EditAnywhere, Category = VFX)
	TMap<FString, TObjectPtr<UNiagaraSystem>>  Map_Vfx;

	UPROPERTY(EditAnywhere, Category = Montage)
	TMap<FString, TObjectPtr<UAnimMontage>>  Map_Montage;
};
