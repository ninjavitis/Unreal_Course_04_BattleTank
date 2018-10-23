// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable)
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * TankAimingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent * TankMovementComponent = nullptr;


private:
	UPROPERTY(EditAnywhere, Category = "Firing Params")
	float LaunchSpeed = 10000.0; //TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3.0f;
	
	UTankBarrel* Barrel = nullptr; //TODO remove

	double LastFireTime = 0;
};
