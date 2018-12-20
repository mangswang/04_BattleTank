// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank"));
	}
	UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing: %s"), *(ControlledTank->GetName()));

	auto PlayerController = GetPlayerTank();
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("No playercontroller found"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Playercontroller found: %s"), *(PlayerController->GetName()));
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}