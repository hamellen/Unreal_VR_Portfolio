// Fill out your copyright notice in the Description page of Project Settings.


#include "MySqlComponent.h"

using namespace std;
// Sets default values for this component's properties
UMySqlComponent::UMySqlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UMySqlComponent::~UMySqlComponent()
{

	CloseDatabaseConnection();
}


// Called when the game starts
void UMySqlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMySqlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UMySqlComponent::ConnectToDataBase(const FString& host, int32 port, const FString& username, const FString& password, const FString& schema)
{

	string str_host = TCHAR_TO_UTF8(*host);
	string str_username = TCHAR_TO_UTF8(*username);
	string str_password = TCHAR_TO_UTF8(*password);
	string str_schema = TCHAR_TO_UTF8(*schema);

	m_Session = new mysqlx::Session(str_host, port, str_username, str_password);
	m_SchemaDB = new mysqlx::Schema(m_Session->getSchema(str_schema));

	return true;
}

bool UMySqlComponent::InsertIntoDatabase(const FString& tablename, const FString& username, const FString& password)
{

	if (m_Session == nullptr) {
	
		return false;
	}

	mysqlx::Table table = m_SchemaDB->getTable(TCHAR_TO_UTF8(*tablename));
	table.insert("user_name", "password").values(TCHAR_TO_UTF8(*username), TCHAR_TO_UTF8(*password));


	return true;
	
}

void UMySqlComponent::CloseDatabaseConnection()
{
	if (m_Session) {
	
		delete m_Session;
		m_Session = nullptr;
	}

	if (m_SchemaDB) {
		delete m_SchemaDB;
		m_SchemaDB = nullptr;
	}

}

