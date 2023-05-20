// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/ItemActivationWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "Item/AstroItemData.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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
	UE_LOG(LogTemp, Log, TEXT("Visible Set"));
	ItemData = Cast<UAstroItemData>(ListItemObject);
	this->SetVisibility(ESlateVisibility::Visible);

	check(ItemData);
	ItemImage->SetBrushFromTexture(ItemData->ItemImage);
	if (ItemData->Type == EItemType::Active)
	{
		ItemActivationWidget->ButtonSet(true);
		ItemActivationWidget->ItemActionButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnActivationItemButton);
		ItemCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), ItemData->ItemCount)));
	}
	else
	{
		ItemActivationWidget->ButtonSet(false);
	}
}

void UInventorySlotWidget::ItemCountChanged(UAstroItemData* InItemData)
{
	ItemData = InItemData;
	if (ItemData->ItemCount <= 0) {
		IAstroHUDInterface* HUD = CastChecked<IAstroHUDInterface>(GetOwningPlayer()->GetHUD());
		HUD->RemoveItem(ItemData);
		return; 
	}
	ItemCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), ItemData->ItemCount)));
}

void UInventorySlotWidget::OnPressedItemButton()
{
	ItemActivationWidget->SetItemActivateWidgetActive();
}

void UInventorySlotWidget::OnActivationItemButton()
{
	
	IAstroItemInterface* ItemUseComponent = CastChecked<IAstroItemInterface>(GetOwningPlayerPawn());

	ItemUseComponent->UseItem(ItemData);
	ItemActivationWidget->SetItemActivateWidgetActive();
	ItemData->ItemCount--;
	ItemCountChanged(this->ItemData);
}

void UInventorySlotWidget::OnHoveredItemButton()
{
	UE_LOG(LogTemp, Log, TEXT("Hovered"));
	IAstroHUDInterface* HUD =  CastChecked<IAstroHUDInterface>(GetOwningPlayer()->GetHUD());
	HUD->TextUpdateWhenHovered(ItemData);
}

void UInventorySlotWidget::UnHoveredItemButton()
{
	IAstroHUDInterface* HUD = CastChecked<IAstroHUDInterface>(GetOwningPlayer()->GetHUD());
	HUD->TextUpdateWhenUnHovered();
	ItemActivationWidget->ItemActionButton->SetVisibility(ESlateVisibility::Hidden);
}



