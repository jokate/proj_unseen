// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacterWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UAstroCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ExploreCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("ExploreBase")));
	HPTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	bool False = false;
	ExploreUIActive(False);
	
}

void UAstroCharacterWidget::HPTextUpdate(uint32& InHp)
{
	FString TextName = FString::Printf(TEXT("Current HP : %d"), InHp);
	HPTextBlock->SetText(FText::FromString(TextName));
}

void UAstroCharacterWidget::ExploreUIActive(bool& InBoolean)
{
	if (nullptr != ExploreCanvas) {
		if (InBoolean)
			ExploreCanvas->SetVisibility(ESlateVisibility::Visible);
		else
			ExploreCanvas->SetVisibility(ESlateVisibility::Hidden);
	}
}
