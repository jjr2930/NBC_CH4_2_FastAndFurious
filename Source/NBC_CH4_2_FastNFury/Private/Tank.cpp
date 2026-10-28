// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "TankController.h"
#include "JUtility.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	TankSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Tank Skeletal Mesh");
	
	Camera->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(RootComponent);
	TankSkeletalMesh->SetupAttachment(GetMesh());
	
	bShouldInverseLookY = true;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	StopTurnInputDegreeThreshold = 25.0;
	
	ATankController* TankController 
		= Cast<ATankController>(GetController());
	JASSERT(IsValid(TankController), "TankController is invalid");
	
	UEnhancedInputComponent* EnhancedInputComponent 
		= Cast<UEnhancedInputComponent>(PlayerInputComponent);
	JASSERT(IsValid(EnhancedInputComponent), "PlayerInputComponent is not UEnhancedInputComponent");
	
	EnhancedInputComponent->BindAction(
		TankController->GetThrottleAction()
		, ETriggerEvent::Triggered
		, this
		, &ATank::OnThrottleInput
	);
	
	EnhancedInputComponent->BindAction(
		TankController->GetThrottleAction()
		, ETriggerEvent::Completed
		, this
		, &ATank::OnThrottleInput
	);
	
	EnhancedInputComponent->BindAction(
	TankController->GetBrakeAction()
		, ETriggerEvent::Triggered
		, this
		, &ATank::OnBrakeInput
	);
	
	EnhancedInputComponent->BindAction(
		TankController->GetBrakeAction()
		, ETriggerEvent::Completed
		, this
		, &ATank::OnBrakeInput
	);
	
	EnhancedInputComponent->BindAction(
		TankController->GetSteeringAction()
		, ETriggerEvent::Started
		, this
		, &ATank::OnSteeringStart
	);
	
	EnhancedInputComponent->BindAction(
		TankController->GetSteeringAction()
		, ETriggerEvent::Triggered
		, this
		, &ATank::OnSteeringInput
	);	
	
	EnhancedInputComponent->BindAction(
		TankController->GetSteeringAction()
		, ETriggerEvent::Completed
		, this
		, &ATank::OnSteeringInput
	);
	
	EnhancedInputComponent->BindAction(
		TankController->GetLookAction()
		, ETriggerEvent::Triggered
		, this
		, &ATank::OnLookInput);
	
	EnhancedInputComponent->BindAction(
		TankController->GetLookAction()
		, ETriggerEvent::Completed
		, this
		, &ATank::OnLookInput);
}

bool ATank::IsStopAddTurnInput() const
{	FVector AngularVelocity = GetMesh()->GetPhysicsAngularVelocityInDegrees();
	return  AngularVelocity.Length() >= StopTurnInputDegreeThreshold;
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	FVector3d Start = Camera->GetComponentLocation();
	FVector3d End = Start + Camera->GetForwardVector() * 10000.0f;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult
		, Start
		, End
		, ECC_Visibility
	);

	
	FVector3d Forward = GetActorForwardVector();
	FVector3d PlanarFoward = FVector3d::VectorPlaneProject(Forward, FVector3d::UpVector);
	FRotator PlanarForwardRotation = PlanarFoward.Rotation();
	FRotator PlanarToTargetRotation(0.0f, 0.0f, 0.0f);
	FVector3d ToTarget(0.0f, 0.0f, 0.0f);
	FVector3d PlanarToTarget(0.0f, 0.0f, 0.0f);
	if (bHit)
	{
		FVector3d HitPoint = HitResult.ImpactPoint;
		FVector3d TankLocation = GetActorLocation();
		ToTarget = HitPoint - TankLocation;		
	}
	else
	{
		ToTarget = End - Start;
	}
	
	FRotator ToTargetRotation = ToTarget.Rotation();
	TotalRotator = FMath::RInterpTo(TotalRotator
		, ToTargetRotation
		, DeltaSeconds
		, TurretInterpSpeed);
	
	TurretAzimuth = TotalRotator.Yaw;
	BarrelElevation = -TotalRotator.Pitch;
	BarrelElevation = BarrelElevationRange.Clamp(BarrelElevation);
}

void ATank::OnThrottleInput(const FInputActionValue& Value)
{
	float ThrottleInput = Value.Get<float>();
	JLog("Throttle : %f", ThrottleInput);
	
	GetVehicleMovementComponent()->SetThrottleInput(ThrottleInput);
}

void ATank::OnSteeringInput(const FInputActionValue& Value)
{
	float SteeringInput = Value.Get<float>();
	JLog("Steering : %f", SteeringInput);
	
	if (IsStopAddTurnInput())
	{
		GetVehicleMovementComponent()->SetYawInput(0.0f);
	}
	else
	{
		GetVehicleMovementComponent()->SetYawInput(SteeringInput);
	}
}

void ATank::OnSteeringStart(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(0.1f);
}

void ATank::OnBrakeInput(const FInputActionValue& Value)
{
	float BrakeInput = Value.Get<float>();
	JLog("Break : %f", BrakeInput);
	
	GetVehicleMovementComponent()->SetBrakeInput(BrakeInput);
}

void ATank::OnLookInput(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	float Elevation = (bShouldInverseLookY) ? -LookInput.Y : LookInput.Y;
	float Azimuth = LookInput.X;
		
	AddControllerYawInput(Azimuth);
	AddControllerPitchInput(Elevation);
}

FOnTankAimChanged& ATank::GetAimChangedDelegate()
{
	return OnTankAimChanged;
}
