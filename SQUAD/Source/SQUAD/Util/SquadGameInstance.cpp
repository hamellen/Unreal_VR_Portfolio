// Fill out your copyright notice in the Description page of Project Settings.



#include "SquadGameInstance.h"

using namespace std;

USquadGameInstance::USquadGameInstance()
{
	

}



USquadGameInstance::~USquadGameInstance()
{
	
	//CloseDatabaseConnection();
}

void USquadGameInstance::Init()
{
	Super::Init();

	//열결 시도 

	//ConnectToDataBase("127.0.0.1", 33060, "root", "0582", "test");

	/*if (m_Session && m_SchemaDB) {
	
		UE_LOG(LogTemp, Warning, TEXT("DataBase Connection Success"));

	}*/

}

//void USquadGameInstance::ConnectToDataBase(const FString& host, int32 port, const FString& username, const FString& password, const FString& schema)
//{
//	string str_host = TCHAR_TO_UTF8(*host);
//	string str_username = TCHAR_TO_UTF8(*username);
//	string str_password = TCHAR_TO_UTF8(*password);
//	string str_schema = TCHAR_TO_UTF8(*schema);
//
//	m_Session = new mysqlx::Session(str_host, port, str_username, str_password);
//	m_SchemaDB = new mysqlx::Schema(m_Session->getSchema(str_schema));
//
//
//
//	
//}

//void USquadGameInstance::CloseDatabaseConnection()
//{
//	if (m_Session) {
//
//		delete m_Session;
//		m_Session = nullptr;
//	}
//
//	if (m_SchemaDB) {
//		delete m_SchemaDB;
//		m_SchemaDB = nullptr;
//	}
//
//}
