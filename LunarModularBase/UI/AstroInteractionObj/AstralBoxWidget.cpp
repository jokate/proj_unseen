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
	CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LoadPanel")));
	PercentTargetImage = Cast<UImage>(GetWidgetFromName(TEXT("Percentage")));
	PercentTargetImage->SetBrushFromMaterial(DynamicUIMaterialInstance);
	SetPercentage(0.0f);
	UpdateVisible(false);
}

void UAstralBoxWidget::VisibilitySet(OnVisible& VisibleFunc)
{
	if (VisibleFunc.IsBound()) {
		UpdateVisible(VisibleFunc.Execute());
	}

}

void UAstralBoxWidget::PercentSet(OnActivate& Activated) 
{
	if (Activated.IsBound()) {
		SetPercentage(Activated.Execute());
	}
}

void UAstralBoxWidget::SetPercentage(float Percentage)
{
	if (nullptr != DynamicUIMaterialInstance)
		DynamicUIMaterialInstance->SetScalarParameterValue("Percent", Percentage);
	if (Percentage > 1.0f) {
		CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
}

void UAstralBoxWidget::UpdateVisible(bool InBoolean)
{
	if (CanvasPanel != nullptr) {
		if (InBoolean) {
			CanvasPanel->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}



