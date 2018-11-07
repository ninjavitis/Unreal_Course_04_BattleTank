// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.generated.h"

// Enum - Aiming States
UENUM(BlueprintType)
enum class EFiringState : uint8
{
	FSE_Locked UMETA(DisplayName="Locked"),
	FSE_Aiming UMETA(DisplayName = "Aiming"),
	FSE_Reloading UMETA(DisplayName = "Reloading"),
	FSE_NoAmmo UMETA(DisplayName = "No Ammo")
};

//Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds Barrel Properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* MyTurret, UTankBarrel* MyBarrel);

	UFUNCTION(BlueprintCallable)
	const int GetCurrentAmmo();

	UFUNCTION(BlueprintCallable)
	void Fire();

	const EFiringState GetFiringState();
	void AimAt(FVector HitLocation);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Enum")
	EFiringState FiringState = EFiringState::FSE_Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	
	// COMPONENT REFERENCE SECTION
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


	// PROJECTILE SECTION
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Firing Params")
	float LaunchSpeed = 100000.0; 
	

	// AIMING SECTION
	void MoveBarrelToward(FVector AimDirection);
	FVector AimDirection;
	bool IsBarrelMoving(FVector AimDirection);
	

	// RELOAD SECTION
	UPROPERTY(EditDefaultsOnly, Category = "Firing Params")
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing Params")
	uint32 CurrentAmmo = 3;
	
	double LastFireTime = 0;
	
	
};
