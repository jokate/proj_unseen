// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/InteractableTriggerComponent.h"
#include "Interface/AstroCharacterInterface.h"
#include "InteractiveObject/InteractiveObject/AstroTriggerResponseObject.h"
// Sets default values for this component's properties
UInteractableTriggerComponent::UInteractableTriggerComponent()
{

}

void UInteractableTriggerComponent::TriggerObjectActive()
{
	auto Player = CastChecked<IAstroCharacterInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Player)
	{
		Player->ActivationComplete(TriggerObject);
	}
}

