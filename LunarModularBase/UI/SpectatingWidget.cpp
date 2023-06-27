// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SpectatingWidget.h"
#include "Components/Image.h"
#include "Interface/AstroMissionClearInterface.h"


USpectatingWidget::USpectatingWidget(const FObjectInitializer& Initializer) : Super(Initializer)
{
	
}

void USpectatingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto Player = CastChecked<IAstroMissionClearInterface>(GetOwningPlayerPawn());
	if(Player->GetLocalPlayerTag() == EPlayerType::PLAYER_BACK) 
	{
		SpectatingView->SetBrushFromMaterial(FrontMat);
	}
	else 
	{
		SpectatingView->SetBrushFromMaterial(BackMat);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void USpectatingWidget::VisibilityButtonPressed()
{
	if (GetVisibility() == ESlateVisibility::Hidden)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}
