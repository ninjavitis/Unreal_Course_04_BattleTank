// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "Tank.h"
#include "Engine/World.h"



ATank* ATankAIController::GetControlledTank() const
{
	return Cast <ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast <ATank>(PlayerPawn);
}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PossessedTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant Find Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank %s targeting %s"), *PossessedTank->GetName(), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetPlayerTank()) { return; }

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}