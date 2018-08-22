// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"




ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast <ATank>(GetPawn());
}

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
