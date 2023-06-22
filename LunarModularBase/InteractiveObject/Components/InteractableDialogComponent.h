// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableDialogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UInteractableDialogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableDialogComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DialogString;

public:	
	UFUNCTION(BlueprintCallable)
	void DialogOnBoard();
		
};
