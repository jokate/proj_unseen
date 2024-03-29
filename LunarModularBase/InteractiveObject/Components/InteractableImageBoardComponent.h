// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableImageBoardComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UInteractableImageBoardComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableImageBoardComponent();

protected:


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoardingImage)
	TObjectPtr<class UTexture2D> BoardingImage;


	UFUNCTION(BlueprintCallable)
	void ImageOnBoard();

	UFUNCTION(BlueprintCallable)
	void ImageSetMaterial(UMaterial* InMaterial);
		
};
