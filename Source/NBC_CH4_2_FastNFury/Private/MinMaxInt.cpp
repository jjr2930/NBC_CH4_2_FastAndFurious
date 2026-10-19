// Fill out your copyright notice in the Description page of Project Settings.


#include "MinMaxInt.h"

FMinMaxInt::FMinMaxInt()
	: Min(0)
	, Max(0)
{
}

FMinMaxInt::FMinMaxInt(int Min, int Max)
	: Min(Min)
	, Max(Max)
{
}

bool FMinMaxInt::Contains(int Value, bool bMinInclusive, bool bMaxInclusive) const
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
