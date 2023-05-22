// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroHUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAstroHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUNARMODULARBASE_API IAstroHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UpdateMissionText(FString& MissionText) = 0;

	virtual void UpdateMissionScriptText(FString& MissionScript) = 0;

	virtual void SetVisibleUserStatus(bool& InVisible) = 0;

	virtual void SetPlayerHPText(uint32& InHp) = 0;

	virtual void AddItem(UObject* InItemData) = 0;

	virtual void ActiveItemWidget() = 0;

	virtual bool ItemContainCheck(class UAstroItemData* InItemData) = 0;

};
