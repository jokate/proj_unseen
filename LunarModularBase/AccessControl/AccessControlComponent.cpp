// Fill out your copyright notice in the Description page of Project Settings.


#include "AccessControl/AccessControlComponent.h"
#include "GameFramework/GameStateBase.h"

#include "Interface/AstroGameStateInterface.h"
#include "Interface/AstroItemInterface.h"
// Sets default values for this component's properties
UAccessControlComponent::UAccessControlComponent()
{
}


bool UAccessControlComponent::CanBeActivated(AActor* InCharacterActor)
{
	if (NeedItemID.IsNone() && NeedMissionIDs.IsEmpty())
		return true;
	return (GameStateChecker() && PlayerItemChecker(InCharacterActor));
}

bool UAccessControlComponent::GameStateChecker()
{
	for (auto NeedMissionID : NeedMissionIDs) {
		IAstroGameStateInterface* AstroInterface = CastChecked<IAstroGameStateInterface>(GetWorld()->GetGameState());
		if (AstroInterface->IsContainMissionID(NeedMissionID))
			return true;
	}
	return false;
}

bool UAccessControlComponent::PlayerItemChecker(AActor* InCharacterActor)
{
	IAstroItemInterface* ItemChecker = CastChecked<IAstroItemInterface>(InCharacterActor);

	return ItemChecker->ContainsItem(NeedItemID);
}
