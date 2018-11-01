// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectBaseUtility.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto TankRightDirection = GetRightVector();
	auto VelocityVector = GetComponentVelocity();

	auto SlippageSpeed = FVector::DotProduct(TankRightDirection, VelocityVector);
	auto SlipAccelerationCorrection = -SlippageSpeed / DeltaTime * TankRightDirection;

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * SlipAccelerationCorrection) / 2;  //divided by 2 as there are 2 tracks applying force
	
	TankRoot->AddForce(CorrectionForce);

	UE_LOG(LogTemp, Warning, TEXT("%s: slip velocity: %f"), *GetName(), SlippageSpeed);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


