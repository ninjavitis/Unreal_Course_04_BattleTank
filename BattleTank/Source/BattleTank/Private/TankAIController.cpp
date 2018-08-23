// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h "
#include "Engine/World.h"
#include "TankAIController.h"


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

