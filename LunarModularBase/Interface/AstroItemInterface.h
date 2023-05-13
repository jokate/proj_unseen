// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAstroItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUNARMODULARBASE_API IAstroItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UseItem(class UAstroItemData* InItemData) = 0;

	virtual bool ContainsItem(FName ItemData) = 0;
};
