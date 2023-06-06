// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroDefinition.h"
#include "AstroMissionClearInterface.generated.h"

DECLARE_DELEGATE_OneParam(FOnActivatedComplete, FName);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAstroMissionClearInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class LUNARMODULARBASE_API IAstroMissionClearInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Req_MissionClear(FName ObjectName) = 0;

	virtual void HUDUpdate(FName InMissionID) = 0;

	virtual EPlayerType ReturnTag() = 0;

	virtual void PlayerTypeSetting(EPlayerType InPlayerType) = 0;

	virtual void TakeItem(class UAstroItemData* InItemData) = 0;

	virtual void OnMissionObjectCollided(FOnActivatedComplete& InActivaedDelegate) = 0;

	virtual EPlayerType GetLocalPlayerTag() = 0;
};
