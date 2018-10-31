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
	FSE_Reloading UMETA(DisplayName = "Reloading")
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

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Enum")
	EFiringState FiringState = EFiringState::FSE_Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;
		
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category = "Firing Params")
	float LaunchSpeed = 10000.0; //TODO find sensible default

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelToward(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3.0f;

	double LastFireTime = 0;

	FVector AimDirection;

	bool IsBarrelMoving(FVector AimDirection);
};
