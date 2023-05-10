// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroDefinition.h"
#include "InteractObjInterface.generated.h"



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractObjInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUNARMODULARBASE_API IInteractObjInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public : 
	virtual void SetObjActiveComplete() = 0;

	virtual void OnActivating() = 0;

	virtual void StopActivating() = 0;
};
