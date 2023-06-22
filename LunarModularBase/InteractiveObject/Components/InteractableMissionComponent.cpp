// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/InteractableMissionComponent.h"
#include "Interface/AstroMissionClearInterface.h"

// Sets default values for this component's properties
UInteractableMissionComponent::UInteractableMissionComponent()
{

}


void UInteractableMissionComponent::MissionCompleted()
{
	auto MissionPlayer = CastChecked<IAstroMissionClearInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(MissionPlayer) 
	{
		MissionPlayer->Req_MissionClear(ObjectID);
	}
}


