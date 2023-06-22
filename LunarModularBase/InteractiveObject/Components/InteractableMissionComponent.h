// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableMissionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UInteractableMissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableMissionComponent();

protected:

public:	
	UPROPERTY(EditAnywhere)
	FName ObjectID = "";

	UFUNCTION(BlueprintCallable)
	void MissionCompleted();
		
};
