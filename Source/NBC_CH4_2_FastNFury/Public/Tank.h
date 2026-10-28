// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "MinMaxFloat.h"
#include "Tank.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionInstance;
class UInputAction;

//DELEGATES
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTankAimChanged, const FVector2D&, AimScreenPosition);

UCLASS()
class NBC_CH4_2_FASTNFURY_API ATank : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void OnThrottleInput(const FInputActionValue& Value);
	void OnSteeringInput(const FInputActionValue& Value);
	void OnSteeringStart(const FInputActionValue& Value);
	void OnBrakeInput(const FInputActionValue& Value);
	void OnLookInput(const FInputActionValue& Value);
		
	FOnTankAimChanged& GetAimChangedDelegate();
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	bool IsStopAddTurnInput() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Components")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Components")	
	TObjectPtr<USkeletalMeshComponent> TankSkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	float StopTurnInputDegreeThreshold;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	bool bShouldInverseLookY;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	FName TurretName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	FName BarrelName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	float BarrelElevation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	FMinMaxFloat BarrelElevationRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	float TurretAzimuth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	FMinMaxFloat TurretAzimuthRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	float DesiredTurretAzimuth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	float DesiredBarrelElevation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	float TurretInterpSpeed = 3.0f;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Delegates")
	FOnTankAimChanged OnTankAimChanged;	
	
	FRotator TurretRotator;
	FRotator TotalRotator;
};
