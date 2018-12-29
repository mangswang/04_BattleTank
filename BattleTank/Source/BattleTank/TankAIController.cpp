// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

		// aim at the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();//TODO limit firing rate
	}
}


