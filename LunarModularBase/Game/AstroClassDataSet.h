// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AstroClassDataSet.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroClassDataSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<APawn>> AstroCharacterClasses;
};
