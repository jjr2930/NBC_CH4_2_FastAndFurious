// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TankAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH4_2_FASTNFURY_API UTankAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
