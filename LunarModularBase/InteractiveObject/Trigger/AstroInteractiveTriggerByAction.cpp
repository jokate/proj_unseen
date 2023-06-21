// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroInteractiveTriggerByAction.h"
#include "Components/SphereComponent.h"
#include "InteractiveObject/Trigger/AstroInteractionTrigger.h"

void AAstroInteractiveTriggerByAction::SetObjActiveComplete()
{
	if(ObjectTrigger->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics) 
	{
		Super::SetObjActiveComplete();
	}
	else 
	{
		ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AAstroTriggerResponseObject::SetObjActiveComplete();
	}
}

void AAstroInteractiveTriggerByAction::SetObjDeActivateComplete()
{
	ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Super::SetObjDeActivateComplete();
}
