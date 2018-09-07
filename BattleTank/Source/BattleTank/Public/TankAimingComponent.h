// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.generated.h"

//Forward declaration
class UTankBarrel;  

// Holds Barrel Properties and Elevate Method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UStaticMeshComponent* TurretToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);


protected:
	// Called when the game starts

private:
	UTankBarrel* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;

	void MoveBarrelToward(FVector AimDirection);
};
