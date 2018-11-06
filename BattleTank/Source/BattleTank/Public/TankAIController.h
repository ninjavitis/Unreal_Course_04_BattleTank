// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

//Forward Declarations

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:

protected:


private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// how close the AI tank will get to the player in cm
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;

	
	UTankAimingComponent* AimingComponent;


};
