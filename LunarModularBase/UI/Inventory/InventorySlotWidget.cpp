// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/ItemActivationWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "Item/AstroItemData.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Interface/AstroItemInterface.h"
#include "Interface/AstroHUDInterface.h"
#include "GameFramework/HUD.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ItemButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnPressedItemButton);
	ItemButton->OnHovered.AddDynamic(this, &UInventorySlotWidget::OnHoveredItemButton);
	ItemButton->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::UnHoveredItemButton);
	
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

	ItemUseComponent->UseItem(ItemData);
	ItemActivationWidget->SetItemActivateWidgetActive();
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
