// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "AstroImageBoardObject.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroImageBoardObject : public AAstroInteractableObject
{
	GENERATED_BODY()
	
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoardingImage)
	TObjectPtr<class UTexture2D> BoardingImage;

	virtual void SetPercentage(float Infloat) override;
};
