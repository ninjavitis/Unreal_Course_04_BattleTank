// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto PossessedTank = GetControlledTank();

	if (!PossessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Possessed Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Begin Play"), *PossessedTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast <ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
		// TODO tell controlled tank to aim at this point
	}
}

// get world location of linterace through crosshair, if it hits the landscape: true
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	// deproject the screen position of the crosshair to world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// linetrace along the look direction and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
		
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;  // not used but expected by the deprojection function

	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

	return true;
}