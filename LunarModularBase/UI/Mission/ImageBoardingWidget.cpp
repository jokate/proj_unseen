// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mission/ImageBoardingWidget.h"
#include "Components/Image.h"
void UImageBoardingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}
void UImageBoardingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (GetVisibility() == ESlateVisibility::Visible)
		OnVisible();
}
void UImageBoardingWidget::ImageWidgetOnBoard(UTexture2D* InTexture)
{
	SetVisibility(ESlateVisibility::Visible);
	ObjectSendImage->SetBrushFromTexture(InTexture);
}

void UImageBoardingWidget::ImageWidgetUnBoard()
{
	SetVisibility(ESlateVisibility::Hidden);
	OnInvisible();
}

void UImageBoardingWidget::OnVisible()
{
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->DisableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = true;
}

void UImageBoardingWidget::OnInvisible()
{
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->EnableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = false;

}
