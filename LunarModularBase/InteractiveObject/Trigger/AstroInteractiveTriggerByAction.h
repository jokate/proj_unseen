// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/Trigger/AstroTriggerInteractiveObject.h"
#include "AstroInteractiveTriggerByAction.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroInteractiveTriggerByAction : public AAstroTriggerInteractiveObject
{
	GENERATED_BODY()
	
public :
	UPROPERTY(BlueprintReadWrite)
	uint8 bIsActions : 1;

	
	virtual void SetObjActiveComplete() override;

	virtual void SetObjDeActivateComplete() override;

	virtual void CheckActivationByTrigger() override;
};
