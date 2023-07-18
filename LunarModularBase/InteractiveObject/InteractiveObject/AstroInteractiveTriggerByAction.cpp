// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroInteractiveTriggerByAction.h"
#include "Components/SphereComponent.h"
#include "InteractiveObject/Trigger/AstroInteractionTrigger.h"

AAstroInteractiveTriggerByAction::AAstroInteractiveTriggerByAction()
{
	bIsReadyToActions = false;
}

void AAstroInteractiveTriggerByAction::SetObjActiveComplete()
{
	if(bIsReadyToActions == true) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Activated"))
		Super::SetObjActiveComplete();
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Ready To Activated"))
		ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		bIsActivated = true;
		K2_OnObjectReadyToAction();
		bIsReadyToActions = true;
	}
}

void AAstroInteractiveTriggerByAction::SetObjDeActivateComplete()
{
	bIsReadyToActions = false;
	ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Super::SetObjDeActivateComplete();
}
