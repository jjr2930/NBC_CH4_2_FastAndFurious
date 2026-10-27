// Fill out your copyright notice in the Description page of Project Settings.


#include "MinMaxFloat.h"

FMinMaxFloat::FMinMaxFloat()
	: Min(0.0f)
	, Max(0.0f)
{
}

FMinMaxFloat::FMinMaxFloat(float Min, float Max)
	: Min(Min)
	, Max(Max)
{
}

bool FMinMaxFloat::Contains(float Value, bool bMinInclusive, bool bMaxInclusive) const
{
	if (bMinInclusive && bMaxInclusive)
	{
		return Min <= Value && Value <= Max;
	}
	else if (!bMinInclusive && bMaxInclusive)
	{
		return Min < Value && Value <= Max;
	}
	else if (bMinInclusive && !bMaxInclusive)
	{
		return Min <= Value && Value < Max;
	}
	else
	{
		return Min < Value && Value < Max;
	}
}

float FMinMaxFloat::Clamp(float Value) const
{
	if (Value < Min)
	{
		return Min;
	}
	else if (Value > Max)
	{
		return Max;
	}
	else
	{
		return Value;
	}
}
