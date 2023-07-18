// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "AstroInteractiveTriggerByAction.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroInteractiveTriggerByAction : public AAstroInteractableObject
{
	GENERATED_BODY()
	
public :
	AAstroInteractiveTriggerByAction();

	UPROPERTY(BlueprintReadWrite)
	uint8 bIsReadyToActions : 1;

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnObjectReadyToActionCPP"))
	void K2_OnObjectReadyToAction();

	
	virtual void SetObjActiveComplete() override;

	virtual void SetObjDeActivateComplete() override;

};
