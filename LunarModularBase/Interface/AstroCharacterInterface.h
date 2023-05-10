// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroCharacterInterface.generated.h"



struct FInputActionValue;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAstroCharacterInterface : public UInterface
{
	GENERATED_BODY()
};



/**
 * 
 */
class LUNARMODULARBASE_API IAstroCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UpDown(const FInputActionValue& Value) = 0;
	virtual void LeftRight(const FInputActionValue& Value) = 0;
	virtual void LookUp(const FInputActionValue& Value) = 0;
	virtual void Turn(const FInputActionValue& Value) = 0;
	virtual void Swift(const FInputActionValue& Value) = 0;
	virtual void StopSwift(const FInputActionValue& Value) = 0;
	virtual void Exploring(const FInputActionValue& Value) = 0;
	virtual void UnExploring(const FInputActionValue& Value) = 0;
	virtual void SearchObjectHit(AActor* Obj, bool bInAndOut) = 0;
};
