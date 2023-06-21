// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mission/ImageBoardingWidget.h"
#include "Components/Image.h"
void UImageBoardingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}
void UImageBoardingWidget::ImageWidgetOnBoard(UTexture2D* InTexture)
{
	SetVisibility(ESlateVisibility::Visible);
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->DisableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = true;
	ObjectSendImage->SetBrushFromTexture(InTexture);
}

void UImageBoardingWidget::ImageWidgetUnBoard()
{
	SetVisibility(ESlateVisibility::Hidden);
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->EnableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = false;
}
