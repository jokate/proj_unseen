// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mission/ImageBoardingWidget.h"
#include "Components/Image.h"
void UImageBoardingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	OnVisibilityChanged.AddDynamic(this, &UImageBoardingWidget::OnChangedVisibility);
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
	ObjectSendImage->SetBrushFromTexture(InTexture, true);
}

void UImageBoardingWidget::ImageWidgetUnBoard()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UImageBoardingWidget::ImageWidgetMaterialChange(UMaterial* InMaterial)
{
	ObjectSendImage->SetBrushFromMaterial(InMaterial);
}

void UImageBoardingWidget::OnVisible()
{
	UE_LOG(LogTemp, Warning, TEXT("ACTIVATED"));
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->DisableInput(GetOwningPlayer());
	GetOwningPlayer()->SetShowMouseCursor(true);
}

void UImageBoardingWidget::OnInvisible()
{
	UE_LOG(LogTemp, Warning, TEXT("DISABLED"));
	GetOwningPlayer()->SetShowMouseCursor(false);
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->EnableInput(GetOwningPlayer());
}

void UImageBoardingWidget::OnChangedVisibility(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Hidden)
	{
		OnInvisible();
	}
}
