// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "TankController.h"
#include "JUtility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
	FakeTankMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FakeTankMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	Camera->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(RootComponent);
	FakeTankMesh->SetupAttachment(RootComponent);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	MaxTorque = 1000.0f;
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	ATankController* TankController 
		= Cast<ATankController>(GetController());
	JASSERT(IsValid(TankController), "TankController is invalid");
	
	UEnhancedInputComponent* EnhancedInputComponent 
		= Cast<UEnhancedInputComponent>(PlayerInputComponent);
	JASSERT(IsValid(EnhancedInputComponent), "PlayerInputComponent is not UEnhancedInputComponent");
	
	EnhancedInputComponent->BindAction(
		TankController->GetMoveAction()
		, ETriggerEvent::Triggered
		, this
		, &ATank::OnMoveInput
	);
	
	EnhancedInputComponent->BindAction(
		TankController->GetMoveAction()
		, ETriggerEvent::Completed
		, this
		, &ATank::OnMoveInput
	);
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//forward or backward
	if (FMath::IsNearlyZero(SteeringInput))
	{
		//JLog("No Steering Input");
		LeftTorque = MaxTorque * ThrottleInput;
		RightTorque = MaxTorque * ThrottleInput;
	}
	//with steering
	else
	{
		//JLog("With Steering Input");
		LeftTorque = MaxTorque * SteeringInput * -1.0f;
		RightTorque = MaxTorque * SteeringInput;
	}
	
	UChaosWheeledVehicleMovementComponent* CastedVehicleMovementComponent 
		= Cast<UChaosWheeledVehicleMovementComponent>( GetVehicleMovementComponent());
	
	CastedVehicleMovementComponent->SetThrottleInput( ThrottleInput);
	
	// for (int32 i = LeftWheelIndexRange.Min; i< LeftWheelIndexRange.Max; ++i)
	// {
	// 	CastedVehicleMovementComponent->SetDriveTorque(LeftTorque, i);
	// }
	//
	// for (int32 i = RightWheelIndexRange.Min; i< RightWheelIndexRange.Max; ++i)
	// {
	// 	CastedVehicleMovementComponent->SetDriveTorque(RightTorque, i);
	// }
}

void ATank::OnMoveInput(const FInputActionInstance& Value)
{
	FVector2D MoveInput = Value.GetValue().Get<FVector2D>();
	//x steering, y throttle
	
	ThrottleInput = MoveInput.Y;
	SteeringInput = MoveInput.X;
	
	//JLog("X : %f, Y: %f", MoveInput.X, MoveInput.Y);
}
