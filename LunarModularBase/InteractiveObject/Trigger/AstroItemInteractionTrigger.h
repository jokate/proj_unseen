// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/Trigger/AstroInteractionTrigger.h"
#include "AstroItemInteractionTrigger.generated.h"

/**
 * 
 */
class UAstroActiveItemData;
UCLASS()
class LUNARMODULARBASE_API AAstroItemInteractionTrigger : public AAstroInteractionTrigger
{
	GENERATED_BODY()
	
public :

	AAstroItemInteractionTrigger();

	virtual void BeginPlay();
protected :

	UPROPERTY(EditAnywhere, Category = Item, Meta = (PrivateAccess = "true"))
	TObjectPtr<UAstroActiveItemData> NeedToActivateItem;
	
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
