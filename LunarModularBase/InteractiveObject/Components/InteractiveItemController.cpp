// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/InteractiveItemController.h"
#include "Interface/AstroMissionClearInterface.h"
// Sets default values for this component's properties
UInteractiveItemController::UInteractiveItemController()
{

}


void UInteractiveItemController::ReturnItem()
{
	auto MissionPlayer = CastChecked<IAstroMissionClearInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (MissionPlayer)
	{
		MissionPlayer->TakeItem(ObjectItemData);
	}
}


// Called every frame

