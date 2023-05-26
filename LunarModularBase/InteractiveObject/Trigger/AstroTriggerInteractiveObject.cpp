// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroTriggerInteractiveObject.h"

void AAstroTriggerInteractiveObject::SetObjActiveComplete()
{
	TriggerObject->K2_OnObjectActive();

	Super::SetObjActiveComplete();
}
