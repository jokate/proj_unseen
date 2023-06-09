// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/Trigger/AstroInteractionTrigger.h"
#include "AstroActorInteractionTrigger.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroActorInteractionTrigger : public AAstroInteractionTrigger
{
	GENERATED_BODY()
	
public :

	AAstroActorInteractionTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NeedActor)
	TObjectPtr<AActor> NeedActor;
protected :

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
