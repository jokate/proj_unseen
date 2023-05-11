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

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> ItemTilePanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescriptionText;

public :
	void AddItemData(UObject* ItemData);

	void SetTextData(UAstroItemData* InItemData);
};
