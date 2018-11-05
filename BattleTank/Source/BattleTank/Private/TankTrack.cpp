// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "UObject/UObjectBaseUtility.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySlipCorrectionForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySlipCorrectionForce()
{
	auto TankRightDirection = GetRightVector();
	auto TankVelocity = GetComponentVelocity();
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto SlippageSpeed = FVector::DotProduct(TankRightDirection, TankVelocity);
	auto SlipAccelerationCorrection = -SlippageSpeed / DeltaTime * TankRightDirection;

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
		
	if (ensure(TankRoot)) 
	{
		auto CorrectionForce = (TankRoot->GetMass() * SlipAccelerationCorrection) / 2;  //divided by 2 as there are 2 tracks applying force
		TankRoot->AddForce(CorrectionForce);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s: slip velocity: %f"), *GetName(), SlippageSpeed);
}


void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (ensure(TankRoot))
	{
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}


