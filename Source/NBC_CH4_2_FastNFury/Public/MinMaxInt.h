// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinMaxInt.generated.h"

USTRUCT(BlueprintType)
struct FMinMaxInt
{
	GENERATED_BODY()
	
public:
	FMinMaxInt();
	FMinMaxInt(int Min, int Max);
	~FMinMaxInt() = default;
	
	bool Contains(int Value, bool bMinInclusive = true, bool bMaxInclusive = true) const;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="===Tank===|Properties")
	int32 Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="===Tank===|Properties")
	int32 Max;
};
