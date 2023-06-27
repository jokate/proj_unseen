// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroActorInteractionTrigger.h"
#include "Components/BoxComponent.h"
#include "InteractiveObject/InteractiveObject/AstroTriggerResponseObject.h"
AAstroActorInteractionTrigger::AAstroActorInteractionTrigger()
{
	TriggerVolume->SetCollisionProfileName(TEXT("ObjectDetectionTrigger"));
}

void AAstroActorInteractionTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == NeedActor && !TriggerResponseObject.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("SOMETHING IS OVERLAPPED"))
		bIsTriggered = true;
		for (auto TriggerResponseObj : TriggerResponseObject)
			TriggerResponseObj->CheckActivationByTrigger();
	}
}

void AAstroActorInteractionTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == NeedActor && !TriggerResponseObject.IsEmpty())
	{
		bIsTriggered = false;
		for (auto TriggerResponseObj : TriggerResponseObject)
			TriggerResponseObj->CheckActivationByTrigger();
	}
}


