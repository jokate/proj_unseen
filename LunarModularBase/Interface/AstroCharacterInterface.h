#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroDefinition.h"
#include "AstroCharacterInterface.generated.h"

DECLARE_DELEGATE(FOnCharacterActivateObject);
DECLARE_DELEGATE(FOnCharacterStopActivateObject);

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
	virtual void Move(const FInputActionValue& Value) = 0;
	virtual void LookUp(const FInputActionValue& Value) = 0;
	virtual void Turn(const FInputActionValue& Value) = 0;
	virtual void Swift(const FInputActionValue& Value) = 0;
	virtual void StopSwift(const FInputActionValue& Value) = 0;
	virtual void ActivationComplete(AActor* InActor) = 0;
	virtual FOnCharacterActivateObject& ReturnActivateObjectDelegate() = 0;
	virtual FOnCharacterStopActivateObject& ReturnDeactivateObjectDelegate() = 0;
};