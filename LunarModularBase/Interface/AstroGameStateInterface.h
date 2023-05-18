// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroGameStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAstroGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUNARMODULARBASE_API IAstroGameStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsContainMissionID(FName InMissionID) = 0;

	virtual void SetFrontMissionID(FName InMissionID) = 0;

	virtual void SetBackMissionID(FName InMissionID) = 0;
};
