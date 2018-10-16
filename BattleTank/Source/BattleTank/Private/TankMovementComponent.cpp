// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendedMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw); 
	RightTrack->SetThrottle(Throw);
	
	UE_LOG(LogTemp, Warning, TEXT("Move forward throw: %f"), Throw);

}

void UTankMovementComponent::Initialize(UTankTrack* MyLeftTrack, UTankTrack* MyRightTrack)
{
	if (!MyLeftTrack | !MyRightTrack) { return; }
	LeftTrack = MyLeftTrack;
	RightTrack = MyRightTrack;
}
