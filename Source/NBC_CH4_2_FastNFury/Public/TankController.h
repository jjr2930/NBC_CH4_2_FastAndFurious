// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

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
	virtual void BeginPlay() override;
	
	UInputAction* GetMoveAction() const;
	UInputAction* GetBreakAction() const;
	UInputAction* GetSteeringAction() const;
protected:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputAction> ThrottleAction;
	
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputAction> BreakAction;
	
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category="===TankController===|Inputs")
	TObjectPtr<UInputAction> SteeringAction;
};
