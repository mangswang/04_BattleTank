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

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO move towards player

		// aim at the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}