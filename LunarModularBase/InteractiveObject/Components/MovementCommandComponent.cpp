// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/MovementCommandComponent.h"
#include "Interface/AstroHUDInterface.h"
// Sets default values for this component's properties
UMovementCommandComponent::UMovementCommandComponent()
{
}

void UMovementCommandComponent::MovementCommandActivated()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		auto HUD = CastChecked<IAstroHUDInterface>(PlayerController->GetHUD());
		HUD->SetMovementCommandActive(GetOwner());
	}
}




