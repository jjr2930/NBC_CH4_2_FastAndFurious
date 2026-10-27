// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"

#include "AimWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "GlobalConst.h"
#include "JUtility.h"
#include "Blueprint/UserWidget.h"
#include "Tank.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (!IsLocalPlayerController())
	{
		return;
	}
	
	ATank* Tank = Cast<ATank>(InPawn);
	JASSERT(IsValid(Tank), "Tank is invalid");
	
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	InputSubsystem->AddMappingContext(MappingContext, 0);
		
	JASSERT(IsValid(AimWidget), "Aim Widget is invalid");
	
	UUserWidget* instance = CreateWidget(GetWorld(), AimWidget, TEXT("Aim Widget"));
	AimWidgetInstance = Cast<UAimWidget>(instance);
	AimWidgetInstance->AddToViewport(GlobalConst::AIM_WIDGET_Z_ORDER);
	
	Tank->GetAimChangedDelegate().AddDynamic(AimWidgetInstance, &UAimWidget::SetTankAimImagePosition);
}

UInputAction* ATankController::GetThrottleAction() const
{
	return ThrottleAction;
}

UInputAction* ATankController::GetBrakeAction() const
{
	return BrakeAction;
}

UInputAction* ATankController::GetSteeringAction() const
{
	return SteeringAction;
}

UInputAction* ATankController::GetLookAction() const
{
	return LookAction;;
}
