// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }//e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector OutHitLocation; // out parameter

	bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
	if (bGotHitLocation) // has a side-effect, is going to line trace
	{
		AimingComponent->AimAt(OutHitLocation);
	}
}

//get world location through by linetracing through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that look direction, and see what we hit(up to a max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	//"De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation; // to be discarded
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection));
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
		return false; // line trace didn't succeed
}