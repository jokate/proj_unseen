// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "AstroDialogInteractiveObject.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroDialogInteractiveObject : public AAstroInteractableObject
{
	GENERATED_BODY()
	
public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DialogString;

	virtual void SetPercentage(float Infloat) override;
};
