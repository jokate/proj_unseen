// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ItemActivationWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UItemActivationWidget::NativeConstruct()
{ 
	Super::NativeConstruct();
	ItemActionButton->SetVisibility(ESlateVisibility::Hidden);
	
}

void UItemActivationWidget::SetItemActivateWidgetActive()
{
	if(ItemActionButton->GetVisibility() == ESlateVisibility::Hidden)
		ItemActionButton->SetVisibility(ESlateVisibility::Visible);
	else 
		ItemActionButton->SetVisibility(ESlateVisibility::Hidden);
}

void UItemActivationWidget::ButtonSet(bool bIsItemActive)
{
	ItemActionButton->SetIsEnabled(bIsItemActive);
	if (!bIsItemActive)
		ItemActionText->SetText(FText::FromString(TEXT("작동 불가")));
}
