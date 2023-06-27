// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroDefinition.h"
#include "MovementCommandInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMovementCommandInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUNARMODULARBASE_API IMovementCommandInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void MoveObject(EDirection Vector) = 0;
};
