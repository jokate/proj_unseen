// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroPwInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAstroPwInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUNARMODULARBASE_API IAstroPwInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool ComparePassword(const FString& InPassword) = 0;

	virtual AActor* ReturnTriggerObject() = 0;
};
