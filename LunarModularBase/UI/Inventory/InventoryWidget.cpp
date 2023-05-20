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

void UInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
	ItemTilePanel->ClearListItems();
}

void UInventoryWidget::AddItemData(UObject* ItemData)
{
	if (int32 ItemIndex = ItemTilePanel->GetIndexForItem(ItemData) != -1)
	{
		UE_LOG(LogTemp, Log, TEXT("%d"), ItemIndex);
		UAstroItemData*	ItemData = CastChecked<UAstroItemData>(ItemTilePanel->GetItemAt(ItemIndex - 1));
		ItemUpdate(ItemData);
	}
	else 
	{
		ItemTilePanel->AddItem(ItemData);
	}
}

void UInventoryWidget::DeleteItemData(UObject* ItemData) 
{
	if(ItemTilePanel->GetIndexForItem(ItemData) != -1)
		ItemTilePanel->RemoveItem(ItemData);
}

void UInventoryWidget::SetTextData(UAstroItemData* InItemData)
{
	UE_LOG(LogTemp, Log, TEXT("Item HoverChanged"));
	ItemNameText->SetText(FText::FromString(InItemData->ItemName));
	ItemDescriptionText->SetText(FText::FromString(InItemData->ItemDescription));
}

void UInventoryWidget::SetTextDefault()
{
	ItemNameText->SetText(FText::FromString(TEXT("")));
	ItemDescriptionText->SetText(FText::FromString(TEXT("")));
}

void UInventoryWidget::ItemUpdate(UAstroItemData* ItemData)
{
	UInventorySlotWidget* Widget = CastChecked<UInventorySlotWidget>(ItemTilePanel->GetEntryWidgetFromItem(ItemData));
	Widget->ItemCountUp();
}
