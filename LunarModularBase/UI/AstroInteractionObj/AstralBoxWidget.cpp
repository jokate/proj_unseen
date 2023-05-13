// Fill out your copyright notice in the Description page of Project Settings.


#include "AstralBoxWidget.h"
#include "BoxUIDataAsset.h"
#include <Components/CanvasPanel.h>
#include <Components/Image.h>



UAstralBoxWidget::UAstralBoxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBoxUIDataAsset> UIDATA_ASSET(TEXT("/Game/UI/Box/BoxDataAsset.BoxDataAsset"));

	if (UIDATA_ASSET.Succeeded()) 
	{
		BoxUIDataAsset = UIDATA_ASSET.Object;
	}	
}

void UAstralBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DynamicUIMaterialInstance = UMaterialInstanceDynamic::Create(BoxUIDataAsset->PercentInstance, DynamicUIMaterialInstance);
	DynamicUIMaterialInstance->SetScalarParameterValue("Percent", 0.0f);
	CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LoadPanel")));
	PercentTargetImage = Cast<UImage>(GetWidgetFromName(TEXT("Percentage")));
	PercentTargetImage->SetBrushFromMaterial(DynamicUIMaterialInstance);
	OnPlayerTriggered(false);
}

void UAstralBoxWidget::OnActivateButtonPressed()
{
	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, [&]() {
		SetPercentage(CurrentPercentage + ActivateIncreasePercentage);
	}, ActivateIncreasePercentage, true);
}

FOnActivated& UAstralBoxWidget::ActivatedEventBind()
{
	// TODO: insert return statement here
	return OnActivated;
}

void UAstralBoxWidget::OnActivateButtonReleased()
{
	SetPercentage(0.0f);
	GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
}

void UAstralBoxWidget::SetPercentage(float InPercentage)
{
	CurrentPercentage = InPercentage;
	DynamicUIMaterialInstance->SetScalarParameterValue("Percent", InPercentage);
	if(CurrentPercentage > CompletePercentage)
	{
		OnActivated.ExecuteIfBound();
		OnActivated.Unbind();
		GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
	}
}

void UAstralBoxWidget::OnPlayerTriggered(bool bIsTriggered)
{
	if (bIsTriggered) {
		CanvasPanel->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
}



