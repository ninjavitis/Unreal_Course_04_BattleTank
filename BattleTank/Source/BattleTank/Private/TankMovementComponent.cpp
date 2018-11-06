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
}

void UTankMovementComponent::SlippageSpeed()
{
	auto TankRightDirection = GetOwner()->GetActorRightVector().GetSafeNormal();
	auto VelocityVector = GetOwner()->GetVelocity().GetSafeNormal();

	auto SlippageSpeed = FVector::DotProduct(TankRightDirection, VelocityVector);

	//UE_LOG(LogTemp, Warning, TEXT("%s: slip velocity: %f"), *GetName(), SlippageSpeed);
}

void UTankMovementComponent::IntentMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw); 
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw); 
	RightTrack->SetThrottle(-Throw * 2);
}


