// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/InteractableDialogComponent.h"
#include "Interface/AstroHUDInterface.h"

// Sets default values for this component's properties
UInteractableDialogComponent::UInteractableDialogComponent()
{

}

void UInteractableDialogComponent::DialogOnBoard()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		auto HUD = CastChecked<IAstroHUDInterface>(PlayerController->GetHUD());
		HUD->DialogStringOnBoard(DialogString);
	}
}



