// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/InteractableImageBoardComponent.h"
#include "Interface/AstroHUDInterface.h"
// Sets default values for this component's properties
UInteractableImageBoardComponent::UInteractableImageBoardComponent()
{

}

void UInteractableImageBoardComponent::ImageOnBoard()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		auto HUD = CastChecked<IAstroHUDInterface>(PlayerController->GetHUD());
		HUD->ImageWidgetSet(BoardingImage);
	}
}

void UInteractableImageBoardComponent::ImageSetMaterial(UMaterial* InMaterial)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		auto HUD = CastChecked<IAstroHUDInterface>(PlayerController->GetHUD());
		HUD->SetMaterialOnImageBoard(InMaterial);
	}
}



