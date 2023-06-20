// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "AstroTriggerInteractiveObject.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroTriggerInteractiveObject : public AAstroInteractableObject
{
	GENERATED_BODY()

protected :
	virtual void SetObjActiveComplete() override;

protected:

	UPROPERTY(EditAnywhere, Meta = (PrivateAccess = "true"))
	TObjectPtr<AAstroTriggerResponseObject> TriggerObject;
};
