// Fill out your copyright notice in the Description page of Project Settings.


#include "AccessControl/AccessControlComponent.h"
#include "GameFramework/GameStateBase.h"

#include "Interface/AstroGameStateInterface.h"
#include "Item/AstroItemData.h"
#include "Interface/AstroItemInterface.h"
// Sets default values for this component's properties
UAccessControlComponent::UAccessControlComponent()
{
}


bool UAccessControlComponent::CanBeActivated(AActor* InCharacterActor)
{
	if (!NeedItemData && NeedMissionIDs.IsEmpty())
		return true;
	return (GameStateChecker() && PlayerItemChecker(InCharacterActor));
}

bool UAccessControlComponent::GameStateChecker()
{
	if (NeedMissionIDs.IsEmpty())
		return true;
	for (auto NeedMissionID : NeedMissionIDs) {
		IAstroGameStateInterface* AstroInterface = CastChecked<IAstroGameStateInterface>(GetWorld()->GetGameState());
		if (AstroInterface->IsContainMissionID(NeedMissionID))
			return true;
	}
	return false;
}

bool UAccessControlComponent::PlayerItemChecker(AActor* InCharacterActor)
{
	if (!NeedItemData)
		return true;
	IAstroItemInterface* ItemChecker = Cast<IAstroItemInterface>(InCharacterActor);
	if(ItemChecker)
		return ItemChecker->ContainsItem(NeedItemData);
	return false;
}
