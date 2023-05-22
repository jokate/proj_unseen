// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/ItemActivationWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "Item/AstroItemData.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ListViewBase.h"

#include "Interface/AstroItemInterface.h"
#include "Interface/AstroHUDInterface.h"
#include "GameFramework/HUD.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ItemButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnPressedItemButton);
	ItemButton->OnHovered.AddDynamic(this, &UInventorySlotWidget::OnHoveredItemButton);
	ItemButton->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::UnHoveredItemButton);
	this->SetVisibility(ESlateVisibility::Visible);
}

void UInventorySlotWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	ItemData = Cast<UAstroItemData>(ListItemObject);

	check(ItemData);
	ItemImage->SetBrushFromTexture(ItemData->ItemImage);
	if (ItemData->Type == EItemType::Active)
	{
		ItemActivationWidget->ButtonSet(true);
		ItemActivationWidget->ItemActionButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnActivationItemButton);
		UInventoryWidget* Widget = Cast<UInventoryWidget>(GetOwningListView()->GetOuter()->GetOuter());
		if (Widget)
		{
			ItemCountTextUpdate(Widget->GetItemCount(this->ItemData));
		}
	}
	else
	{
		ItemActivationWidget->ButtonSet(false);
	}
}


void UInventorySlotWidget::OnPressedItemButton()
{
	ItemActivationWidget->SetItemActivateWidgetActive();
}

void UInventorySlotWidget::OnActivationItemButton()
{	
	IAstroItemInterface* ItemUseComponent = CastChecked<IAstroItemInterface>(GetOwningPlayerPawn());

	UInventoryWidget* Widget = Cast<UInventoryWidget>(GetOwningListView()->GetOuter()->GetOuter());
	if (Widget)
	{
		Widget->ItemCountDown(ItemData);
	}
	ItemUseComponent->UseItem(ItemData);
	ItemActivationWidget->SetItemActivateWidgetActive();
}

void UInventorySlotWidget::OnHoveredItemButton()
{
	UE_LOG(LogTemp, Log, TEXT("Hovered"));
	UInventoryWidget* Widget = Cast<UInventoryWidget>(GetOwningListView()->GetOuter()->GetOuter());
	if (Widget)
	{
		Widget->SetTextData(this->ItemData);
	}
}

void UInventorySlotWidget::UnHoveredItemButton()
{
	UInventoryWidget* Widget = Cast<UInventoryWidget>(GetOwningListView()->GetOuter()->GetOuter());
	if (Widget)
	{
		Widget->SetTextDefault();
	}
	ItemActivationWidget->ItemActionButton->SetVisibility(ESlateVisibility::Hidden);
}

void UInventorySlotWidget::ItemCountTextUpdate(int32 ItemCount)
{
	ItemCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), ItemCount)));
}



