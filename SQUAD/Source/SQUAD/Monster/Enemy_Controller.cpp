// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Controller.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../Player/Squad_Pawn.h"
#include "../Monster/EnemySoldier.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
AEnemy_Controller::AEnemy_Controller()
{

	AI_Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_Perception"));
	SetPerceptionComponent(*AI_Perception);

	AI_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI_Sight"));

	AI_Perception->ConfigureSense(*AI_Sight);

	AI_Perception->SetDominantSense(AI_Sight->GetSenseImplementation());
	AI_Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy_Controller::OnTargetPerceptionUpdated);
}

void AEnemy_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Enemy OnPossess"));

	
}

void AEnemy_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (AI_Perception)
	{
		AI_Perception->RegisterComponent();
	}

	soldier = Cast<AEnemySoldier>(GetPawn());
}

void AEnemy_Controller::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	soldier = Cast<AEnemySoldier>(GetPawn());

	if (Actor->IsA(ASquad_Pawn::StaticClass()))  // 특정 액터만 감지
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Player Detected"));

			if (Blackboard) {
				Blackboard->SetValueAsObject(TEXT("Player"), Actor);
				soldier->ReadyToFire = true;
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Player UnDetected"));
			if (Blackboard) {
				Blackboard->SetValueAsObject(TEXT("Player"), nullptr);
				soldier->ReadyToFire = false;
			}

		}
	}


}
