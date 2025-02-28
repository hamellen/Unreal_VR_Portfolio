// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "../Player/Squad_Hand.h"
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
	SetPhysics(false);
	bheld = true;
	OwingHand = TargetHand;

	
	GetOwner()->AttachToComponent(TargetHand->hand_mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void UGrabComponent::UnBind()
{
	SetPhysics(true);
	bheld = false;
	OwingHand = nullptr;
	GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void UGrabComponent::TryTrigger()
{
	if (bheld) {
	
		if (grabtrigger.IsBound()) {
			grabtrigger.Broadcast();
		}
	}

}



