// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroTriggerInteractiveObject.h"

void AAstroTriggerInteractiveObject::SetObjActiveComplete()
{
	TriggerObject->SetObjActiveComplete();

	Super::SetObjActiveComplete();
}
