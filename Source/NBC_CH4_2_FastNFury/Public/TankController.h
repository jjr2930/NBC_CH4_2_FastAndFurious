// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

class UAimWidget;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class NBC_CH4_2_FASTNFURY_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UInputAction* GetThrottleAction() const;
	UInputAction* GetBrakeAction() const;
	UInputAction* GetSteeringAction() const;
	UInputAction* GetLookAction() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputAction> ThrottleAction;
	
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputAction> BrakeAction;
	
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputAction> SteeringAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===TankController===|Inputs")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="===Tank===|Properties")	
	TSubclassOf<UUserWidget> AimWidget;
	
	TObjectPtr<UAimWidget> AimWidgetInstance;
};
