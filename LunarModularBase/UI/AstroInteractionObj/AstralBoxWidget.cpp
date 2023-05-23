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

void UAstralBoxWidget::SetPercentage(float InPercentage)
{
	if(DynamicUIMaterialInstance)
		DynamicUIMaterialInstance->SetScalarParameterValue("Percent", InPercentage);
}

void UAstralBoxWidget::OnPlayerTriggered(bool bIsTriggered)
{
	if (!CanvasPanel)
		return;
	if (bIsTriggered) {
		CanvasPanel->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
}



