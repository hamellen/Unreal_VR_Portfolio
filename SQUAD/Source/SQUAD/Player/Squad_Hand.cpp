// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad_Hand.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASquad_Hand::ASquad_Hand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Base_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Base_Root"));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh>HAND_MESH(TEXT("SkeletalMesh'/Game/MaleHand/Mesh/FirstPersonHand.FirstPersonHand'"));
	motioncontroller = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	motioncontroller->SetupAttachment(Base_Root);

	hand_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand_Mesh"));
	hand_mesh->SetupAttachment(motioncontroller);

	if (HAND_MESH.Succeeded()) {
		hand_mesh->SetSkeletalMesh(HAND_MESH.Object);
	}
}

// Called when the game starts or when spawned
void ASquad_Hand::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASquad_Hand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

