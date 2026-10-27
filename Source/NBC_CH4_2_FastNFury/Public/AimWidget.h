// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tank.h"
#include "AimWidget.generated.h"

class UImage;

UCLASS()
class NBC_CH4_2_FASTNFURY_API UAimWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetTankAimImagePosition(const FVector2D& ScreenPosition);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr< UImage > TankAimImage;
};
