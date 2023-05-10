// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BoxUIDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UBoxUIDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>  PercentInstance;

	UPROPERTY(EditDefaultsonly, BlueprintReadOnly)
	float DefaultPercentage;

};
