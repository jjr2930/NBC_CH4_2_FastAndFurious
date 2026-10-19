// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalPlayerController())
	{
		return;
	}
	
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	InputSubsystem->AddMappingContext(MappingContext, 0);
	
	
}

UInputAction* ATankController::GetMoveAction() const
{
	return ThrottleAction;
}

UInputAction* ATankController::GetBreakAction() const
{
	return BreakAction;
}

UInputAction* ATankController::GetSteeringAction() const
{
	return SteeringAction;
}
