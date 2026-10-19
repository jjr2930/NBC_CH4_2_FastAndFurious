// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "MinMaxInt.h"
#include "Tank.generated.h"

class UCameraComponent;
class USpringArmComponent;
struct FInputActionInstance;
class UInputAction;

UCLASS()
class NBC_CH4_2_FASTNFURY_API ATank : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void OnMoveInput(const FInputActionInstance& Value);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Components")
	TObjectPtr<USkeletalMeshComponent> FakeTankMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Components")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	float MaxTorque;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	FMinMaxInt LeftWheelIndexRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")
	FMinMaxInt RightWheelIndexRange;
	
	float ThrottleInput;
	float SteeringInput;
	float LeftTorque;
	float RightTorque;
};
