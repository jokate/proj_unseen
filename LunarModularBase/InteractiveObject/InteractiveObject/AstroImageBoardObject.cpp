// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroImageBoardObject.h"
#include "Interface/InteractionWidgetInterface.h"
#include "Components/WidgetComponent.h"
#include "Interface/AstroHUDInterface.h"

void AAstroImageBoardObject::SetPercentage(float Infloat)
{
	ActivationPercent = Infloat;
	IInteractionWidgetInterface* Widget = Cast<IInteractionWidgetInterface>(ActivationWidget->GetWidget());
	if (Widget) {
		Widget->SetPercentage(ActivationPercent);
		if (ActivationPercent > ActivationFullPercent)
		{
			SetObjActiveComplete();
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

			if (PlayerController)
			{
				auto HUD = CastChecked<IAstroHUDInterface>(PlayerController->GetHUD());
				HUD->ImageWidgetSet(BoardingImage);
				SetPercentage(0.0f);
			}
			GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
		}
	}
}
