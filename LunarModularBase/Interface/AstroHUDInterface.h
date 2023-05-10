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

	UFUNCTION()
	virtual void UpdateMissionScriptText(FString& MissionScript) = 0;

	UFUNCTION()
	virtual void SetVisibleUserStatus(bool& InVisible) = 0;

	UFUNCTION()
	virtual void SetPlayerHPText(uint32& InHp) = 0;
};
