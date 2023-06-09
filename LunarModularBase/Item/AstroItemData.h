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
	
	bool operator==(const UAstroItemData& InOther) const 
	{
		return ItemID == InOther.ItemID;
	}

	friend FORCEINLINE uint32 GetTypeHash(const UAstroItemData& InItemData) 
	{
		return GetTypeHash(InItemData.ItemID);
	}
	
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


	virtual bool IsNameStableForNetworking() const override
	{
		return true;
	};

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}
};
