// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* MyLeftTrack, UTankTrack* MyRightTrack)
{
	LeftTrack = MyLeftTrack;
	RightTrack = MyRightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow =	FVector::DotProduct(TankForwardDirection, AIForwardIntention);

	auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;

	IntentMoveForward(ForwardThrow);
	IntentTurnRight(RightThrow);

	UE_LOG(LogTemp, Warning, TEXT("%s move velocity: %s"),*GetOwner()->GetName(), *AIForwardIntention.ToString())
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

