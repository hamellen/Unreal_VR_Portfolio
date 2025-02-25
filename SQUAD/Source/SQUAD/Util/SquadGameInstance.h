// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include	<xdevapi.h>
#include "SquadGameInstance.generated.h"



/**
 * 
 */
UCLASS()
class SQUAD_API USquadGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	mysqlx::Session* m_Session;
	mysqlx::Schema* m_SchemaDB;

public:
	USquadGameInstance();
		
	~USquadGameInstance();

public:

	virtual void Init() override;

	void ConnectToDataBase(const FString& host, int32 port, const FString& username, const FString& password, const FString& schema);

	

	void CloseDatabaseConnection();

};
