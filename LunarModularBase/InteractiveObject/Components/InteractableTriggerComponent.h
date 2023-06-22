// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableTriggerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UInteractableTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableTriggerComponent();

	UPROPERTY(EditAnywhere, Meta = (PrivateAccess = "true"))
	TObjectPtr<class AAstroTriggerResponseObject> TriggerObject;
	
	UFUNCTION(BlueprintCallable)
	void TriggerObjectActive();
		
};
