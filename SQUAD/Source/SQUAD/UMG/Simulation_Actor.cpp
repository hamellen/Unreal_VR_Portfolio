// Fill out your copyright notice in the Description page of Project Settings.


#include "Simulation_Actor.h"
#include "Components/WidgetComponent.h"
#include "Situation_Bar.h"
#include "NiagaraComponent.h"
// Sets default values
ASimulation_Actor::ASimulation_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>Cl_Simul(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UMG/Simulatin_Bar.Simulatin_Bar_C'"));

	Simul_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget_Component"));

	if (Cl_Simul.Succeeded()) {
	
		Cl_Simulation = Cl_Simul.Class;
		Simul_Component->SetWidgetClass(Cl_Simulation);
		Simul_Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Simul_Component->SetWidgetSpace(EWidgetSpace::World);
		Simul_Component->SetDrawSize(FVector2D(200.f, 200.f));
	}

	UI_Ray= CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Component"));
}

// Called when the game starts or when spawned
void ASimulation_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	Simul_Object = Cast<USituation_Bar>(Simul_Component->GetWidget());

	Simul_Object->SetTextLeftTreasure();
}

// Called every frame
void ASimulation_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

