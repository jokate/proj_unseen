// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/InteractivePasswordComponent.h"
#include "Interface/AstroHUDInterface.h"

// Sets default values for this component's properties
UInteractivePasswordComponent::UInteractivePasswordComponent()
{

}

void UInteractivePasswordComponent::PasswordWidgetOnBoard()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		auto HUD = CastChecked<IAstroHUDInterface>(PlayerController->GetHUD());
		HUD->SetPasswordVisible(this);

	}
}

bool UInteractivePasswordComponent::ComparePassword(const FString& InPassword)
{
	if(PasswordString.Equals(InPassword)) 
	{
		PasswordEvent.Broadcast();
	}
	return PasswordString.Equals(InPassword);
}

