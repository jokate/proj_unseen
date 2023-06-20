// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroTriggerResponseObject.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveObject/Trigger/AstroInteractionTrigger.h"

// Sets default values
AAstroTriggerResponseObject::AAstroTriggerResponseObject()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
}

// Called when the game starts or when spawned
void AAstroTriggerResponseObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAstroTriggerResponseObject::CheckActivationByTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("ACTIVATION Check START"))
	if (NeedToTrigger.IsEmpty())
		return;
	for(auto Trigger : NeedToTrigger) 
	{
		if(!Trigger->bIsTriggered) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Something Is Not Activating"))
			if (bIsActivated) {
				UE_LOG(LogTemp, Warning, TEXT("DEACTIVATED"))
				SetObjDeActivateComplete();
			}
			return;
		}
	}

	SetObjActiveComplete();
}

void AAstroTriggerResponseObject::SetObjActiveComplete()
{
	bIsActivated = true;
	K2_OnObjectActive();
}

void AAstroTriggerResponseObject::SetObjDeActivateComplete()
{
	bIsActivated = false;
	K2_OnObjectDeactive();
}
