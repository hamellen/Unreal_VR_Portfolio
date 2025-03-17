// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "../Player/Squad_Hand.h"
#include "MotionControllerComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Weapon/AK_Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "../UMG/PlayerStat_Actor.h"
#include "../UMG/Player_Stat.h"
// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	

	//PlayerStat = Cast<APlayerStat_Actor>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStat_Actor::StaticClass()));
}


// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrabComponent::SetPhysics(bool bPhysics)
{
	Cast<UPrimitiveComponent>(GetAttachParent())->SetSimulatePhysics(bPhysics);

}

void UGrabComponent::Bind(TObjectPtr<ASquad_Hand>  TargetHand)
{
	if (grab_type == EGrabEnum::Free) {
		SetPhysics(false);
		bheld = true;
		OwingHand = TargetHand;
		GetOwner()->AttachToComponent(TargetHand->hand_mesh->GetAttachParent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
	else if (grab_type == EGrabEnum::ObjectToHand) {


		SetPhysics(false);
		bheld = true;
		OwingHand = TargetHand;
		GetOwner()->AttachToComponent(TargetHand->scene_object, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


	}
	else if (grab_type == EGrabEnum::HandToObject) {



	}
	
	//CheckWeapon();
}

void UGrabComponent::UnBind()
{
	auto hand = Cast<ASquad_Hand>(GetOwner()->GetAttachParentActor());
	if (hand) {
		hand->GrabCom = nullptr;
	}
	
	
	SetPhysics(true);
	bheld = false;
	OwingHand = nullptr;
	GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//CheckWeapon();
}

void UGrabComponent::TryTrigger()
{
	if (bheld) {
	
		if (grabtrigger.IsBound()) {
			grabtrigger.Broadcast();
		}
	}

}

void UGrabComponent::CheckWeapon()
{
	

	if (GetOwner()->IsA(APlayerStat_Actor::StaticClass())) {

		PlayerStat->Player_Stat->SwitchImage();
	}

}

FRotator UGrabComponent::InvertRotator(const FRotator& Rotator)
{
	return FRotator(
		-Rotator.Pitch,
		-Rotator.Yaw,
		-Rotator.Roll
	);

	
}



