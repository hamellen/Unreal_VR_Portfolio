// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad_Hand.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Animation/Hand_instance.h"
#include "../Component/GrabComponent.h"
#include "../Weapon/Rifle.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../Weapon/Magazine.h"
#include "../Collectable.h"
#include "../Player/Squad_Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetInteractionComponent.h"
// Sets default values
ASquad_Hand::ASquad_Hand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>HAND_MESH(TEXT("SkeletalMesh'/Game/MaleHand/Mesh/FirstPersonHand.FirstPersonHand'"));
	motioncontroller = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	
	Laser = CreateDefaultSubobject<USceneComponent>(TEXT("Laser"));
	Laser->SetupAttachment(motioncontroller);

	Capsule_Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule_Collision->SetupAttachment(motioncontroller);

	hand_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand_Mesh"));
	hand_mesh->SetupAttachment(motioncontroller);

	if (HAND_MESH.Succeeded()) {
		hand_mesh->SetSkeletalMesh(HAND_MESH.Object);
	}
	scene_object = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	scene_object->SetupAttachment(hand_mesh);

	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	WidgetInteraction->SetupAttachment(Laser);
}

// Called when the game starts or when spawned
void ASquad_Hand::BeginPlay()
{
	Super::BeginPlay();
	
	hand_instance= Cast<UHand_instance>(hand_mesh->GetAnimInstance());
	if (!hand_instance) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("No hand instance"));
	}
	mesh_transform = hand_mesh->GetRelativeTransform();


	Squad_Pawn_Object = Cast<ASquad_Pawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

// Called every frame
void ASquad_Hand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquad_Hand::Grab()
{
	if (GrabCom) {//이미 Grab중 
		//바인딩 해체 작업
		GrabCom->UnBind();
		GrabCom = nullptr;
		hand_instance->Pose_Index = 0;
		return;
	}

	//Grab 없음
	GrabCom = FindGrabComponent();// Grab 발견
	if (GrabCom) {//바인딩 작업

		hand_instance->Pose_Index = 50;
		GrabCom->Bind(this);
		
	}
	else if (!GrabCom) {
	
		hand_instance->Pose_Index = -50;
	}
	
}

void ASquad_Hand::Release()
{
	if (GrabCom) {
		return;
	}

	
	hand_instance->Pose_Index = 0;

}

void ASquad_Hand::Trigger()
{
	if (GrabCom) {
		GrabCom->TryTrigger();
	}
	
}

void ASquad_Hand::ResetHandMesh()
{
	hand_mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	hand_mesh->AttachToComponent(motioncontroller, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	hand_mesh->SetRelativeTransform(mesh_transform,false,nullptr,ETeleportType::TeleportPhysics);
	hand_instance->Pose_Index = 0;
}

void ASquad_Hand::OnGetTreasure(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (Hit.GetActor()->IsA(ACollectable::StaticClass())) {
	
		

		Squad_Pawn_Object->current_number_goal++;
		
		OtherActor->Destroy();
	}



}



class UGrabComponent* ASquad_Hand::FindGrabComponent()
{
	FVector motion_location = motioncontroller->GetComponentLocation();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);

	

	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		motion_location,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(secsing_rad),
		CollisionQueryParam);

	if (bResult) {

		TObjectPtr<ARifle> rifle = Cast<ARifle>(OverlapResults[0].GetActor());

		if (rifle) {
			
			return rifle->FindComponentByClass<UGrabComponent>();

		}
		TObjectPtr<AMagazine> magazine = Cast<AMagazine>(OverlapResults[0].GetActor());

		if (magazine) {
		
			
			return magazine->FindComponentByClass<UGrabComponent>();
		}

	}
	

	return nullptr;
}


