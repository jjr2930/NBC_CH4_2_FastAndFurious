// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinMaxFloat.generated.h"

USTRUCT(BlueprintType)
struct FMinMaxFloat
{
GENERATED_BODY()
	
public:
	FMinMaxFloat();
	FMinMaxFloat(float Min, float Max);
	bool Contains(float Value, bool bMinInclusive = true, bool bMaxInclusive = true) const;
	float Clamp(float Value) const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="===Tank===|Properties")
	float Min;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="===Tank===|Properties")
	float Max;
};
