// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand_instance.h"

void UHand_instance::NativeInitializeAnimation()
{


}

void UHand_instance::NativeUpdateAnimation(float DeltaSeconds)
{

	Current_Pose_Index = FMath::Lerp(Current_Pose_Index, Pose_Index, DeltaSeconds* Hand_Speed);
}
