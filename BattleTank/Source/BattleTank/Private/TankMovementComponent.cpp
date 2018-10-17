// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* MyLeftTrack, UTankTrack* MyRightTrack)
{
	LeftTrack = MyLeftTrack;
	RightTrack = MyRightTrack;
}

void UTankMovementComponent::IntentMoveForward(float Throw)
{
	if (!LeftTrack | !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw); 
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!LeftTrack | !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

