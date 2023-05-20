// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AstroItemData.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8 {
	Active = 0,
	Passive,
};
/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	
	
	virtual void BeginDestroy() override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemSprite)
	TObjectPtr<UTexture2D> ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemID)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemName)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemDescription)
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemCount)
	int32 ItemCount = 1;
};
