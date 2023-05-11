// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "Item/AstroItemData.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::AddItemData(UObject* ItemData)
{
	ItemTilePanel->AddItem(ItemData);
}

void UInventoryWidget::SetTextData(UAstroItemData* InItemData)
{
	UE_LOG(LogTemp, Log, TEXT("Item HoverChanged"));
	ItemNameText->SetText(FText::FromString(InItemData->ItemName));
	ItemDescriptionText->SetText(FText::FromString(InItemData->ItemDescription));
}
