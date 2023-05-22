// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "Item/AstroItemData.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->SetVisibility(ESlateVisibility::Hidden);
}

bool UInventoryWidget::IsItemContains(UAstroItemData* Item)
{
	return ItemCounter.Contains(Item);
}

void UInventoryWidget::AddItemData(UObject* ItemData)
{
	if(ItemTilePanel->GetIndexForItem(ItemData) == -1)
		ItemTilePanel->AddItem(ItemData);
	ItemCountUp(CastChecked<UAstroItemData>(ItemData));
}

void UInventoryWidget::DeleteItemData(UObject* ItemData) 
{
	if (ItemTilePanel->GetIndexForItem(ItemData) != -1)
		ItemTilePanel->RemoveItem(ItemData);
}


void UInventoryWidget::SetTextData(UAstroItemData* InItemData)
{
	ItemNameText->SetText(FText::FromString(InItemData->ItemName));
	ItemDescriptionText->SetText(FText::FromString(InItemData->ItemDescription));
}

void UInventoryWidget::SetTextDefault()
{
	ItemNameText->SetText(FText::FromString(TEXT("")));
	ItemDescriptionText->SetText(FText::FromString(TEXT("")));
}

void UInventoryWidget::ItemCountUp(UAstroItemData* ItemData)
{
	if (ItemCounter.Find(ItemData))
	{
		ItemCounter[ItemData]++;
	}
	else
		ItemCounter.Add(ItemData, 1);

	auto Item = Cast<UInventorySlotWidget>(ItemTilePanel->GetEntryWidgetFromItem(ItemData));
	if(Item)
		Item->ItemCountTextUpdate(ItemCounter[ItemData]);
}

void UInventoryWidget::ItemCountDown(UAstroItemData* ItemData)
{
	if (ItemCounter.Find(ItemData))
	{
		if (--ItemCounter[ItemData] <= 0)
		{
			ItemCounter.Remove(ItemData);
			DeleteItemData(ItemData);
			return;
		}
	}
	else
		return;

	auto Item = Cast<UInventorySlotWidget>(ItemTilePanel->GetEntryWidgetFromItem(ItemData));

	if(Item)
		Item->ItemCountTextUpdate(ItemCounter[ItemData]);
}

int32 UInventoryWidget::GetItemCount(UAstroItemData* ItemData)
{
	return ItemCounter[ItemData];
}
