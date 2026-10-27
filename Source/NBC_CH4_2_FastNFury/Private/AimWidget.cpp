#include "AimWidget.h"

#include "JUtility.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

void UAimWidget::SetTankAimImagePosition(const FVector2D& ScreenPosition)
{
	JASSERT(IsValid(TankAimImage), "TankAimImage is invalid");
	
	// UCanvasPanelSlot* AimImageSlot =  Cast<UCanvasPanelSlot>(TankAimImage->Slot);
	// JASSERT(IsValid(AimImageSlot), "AimImageSlot is invalid");
	//
	// AimImageSlot->SetPosition(ScreenPosition);
}
