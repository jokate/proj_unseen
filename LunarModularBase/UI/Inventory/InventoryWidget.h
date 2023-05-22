// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */

class UTileView;
class UTextBlock;
class UAstroItemData;
UCLASS()
class LUNARMODULARBASE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()


public :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UTileView> ItemTilePanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescriptionText;

	UPROPERTY()
	TMap<UAstroItemData*, int32> ItemCounter;

public :
	bool IsItemContains(UObject* Item);

	void AddItemData(UObject* ItemData);

	void SetTextData(UAstroItemData* InItemData);

	void SetTextDefault();

	void DeleteItemData(UObject* ItemData);

	void ItemCountUp(UAstroItemData* ItemData);

	void ItemCountDown(UAstroItemData* ItemData);

	int32 GetItemCount(UAstroItemData* ItemData);
};
