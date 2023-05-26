// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroItemInteractionTrigger.h"
#include "Components/BoxComponent.h"
#include "InteractiveObject/InteractiveObject/AstroInstallItem.h"
#include "Item/AstroItemDatas.h"

AAstroItemInteractionTrigger::AAstroItemInteractionTrigger()
{
	TriggerVolume->SetCollisionProfileName("ObjectDetectionTrigger");
}

void AAstroItemInteractionTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AAstroItemInteractionTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AAstroItemInteractionTrigger::OnOverlapEnd);
}

void AAstroItemInteractionTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAstroInstallItem* InstalledItem = Cast<AAstroInstallItem>(OtherActor);
	if (InstalledItem) 
	{
		if(NeedToActivateItem == InstalledItem->ActivationItemData && TriggerResponseObject) 
		{
			TriggerResponseObject->K2_OnObjectActive();
		}
	}
}

void AAstroItemInteractionTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (TriggerResponseObject)
	{
		TriggerResponseObject->K2_OnObjectDeactive();
	}
}
