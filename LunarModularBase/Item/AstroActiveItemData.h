// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/AstroItemData.h"
#include "AstroActiveItemData.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EActiveType : uint8
{
	PermanentOperational = 0,
	Installation,
	Consumption,
};

UCLASS()
class LUNARMODULARBASE_API UAstroActiveItemData : public UAstroItemData
{
	GENERATED_BODY()
	
public :
	UAstroActiveItemData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActivationType)
	EActiveType ActivationType;

	UPROPERTY(EditAnywhere, Category = InstallationGroundMesh)
	TSoftObjectPtr<UStaticMesh> InstallationGroundMesh;
};
