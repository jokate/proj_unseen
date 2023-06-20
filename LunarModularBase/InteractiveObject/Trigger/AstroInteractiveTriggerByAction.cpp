// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroInteractiveTriggerByAction.h"
#include "Components/SphereComponent.h"
#include "InteractiveObject/Trigger/AstroInteractionTrigger.h"

void AAstroInteractiveTriggerByAction::SetObjActiveComplete()
{
	if(ObjectTrigger->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger Object Activated"))
		Super::SetObjActiveComplete();
	}
	else 
	{
		ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AAstroTriggerResponseObject::SetObjActiveComplete();

		UE_LOG(LogTemp, Warning, TEXT("Object Ready To Go"))
	}
}

void AAstroInteractiveTriggerByAction::SetObjDeActivateComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger DeActivated"))
	ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Super::SetObjDeActivateComplete();
}

void AAstroInteractiveTriggerByAction::CheckActivationByTrigger()
{
	if (NeedToTrigger.IsEmpty())
		return;
	for (auto Trigger : NeedToTrigger)
	{
		if (!Trigger->bIsTriggered)
		{
			if (bIsActivated) {
				UE_LOG(LogTemp, Warning, TEXT("DEACTIVATED"))
				SetObjDeActivateComplete();
			}
			return;
		}
	}

	SetObjActiveComplete();
}
