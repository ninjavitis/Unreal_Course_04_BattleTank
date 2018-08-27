// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ATank * GetControlledTank() const;

	// Move the Tank Barrel so that the projectile trajectory
	// intersects the world at the crosshair
	void AimTowardCrosshair();

	
private:
	bool GetSightRayHitLocation(FVector& HitLocation) const;

};