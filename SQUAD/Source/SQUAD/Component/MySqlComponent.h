// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include	<xdevapi.h>
#include "MySqlComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SQUAD_API UMySqlComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMySqlComponent();
	~UMySqlComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:

	bool ConnectToDataBase(const FString& host, int32 port, const FString& username, const FString& password, const FString& schema);

	bool InsertIntoDatabase(const FString& tablename, const FString& username, const FString& password);

	void CloseDatabaseConnection();

public:

	mysqlx::Session* m_Session;
	mysqlx::Schema* m_SchemaDB;
};
