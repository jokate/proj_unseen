// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroDialogInteractiveObject.h"
#include "Components/WidgetComponent.h"
#include "Interface/InteractableObjectInterface.h"
#include "Interface/AstroHUDInterface.h"
#include "Interface/InteractionWidgetInterface.h"

void AAstroDialogInteractiveObject::SetPercentage(float Infloat)
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
				HUD->DialogStringOnBoard(DialogString);
				SetPercentage(0.0f);
			}
			GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
		}
	}
}
