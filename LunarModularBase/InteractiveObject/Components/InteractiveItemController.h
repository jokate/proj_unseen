// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveItemController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UInteractiveItemController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractiveItemController();

protected:

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (PrivateAccess = "true"), Category = ItemData)
	TObjectPtr<class UAstroItemData> ObjectItemData;

	UFUNCTION(BlueprintCallable)
	void ReturnItem();
};
