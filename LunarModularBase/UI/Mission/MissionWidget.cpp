// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mission/MissionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

UMissionWidget::UMissionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMissionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MissionTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("MissionText")));
	MissionBorder = Cast<UBorder>(GetWidgetFromName(TEXT("MissionBorder")));
	MissionScriptBorder = Cast<UBorder>(GetWidgetFromName(TEXT("MissionScriptBorder")));
	MissionScriptTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("MissionScriptText")));
}

void UMissionWidget::UpdateMissionWidget(FString& MissionDescription)
{
	MissionTextBlock->SetText(FText::FromString(MissionDescription));
}

void UMissionWidget::UpdateMissionScript(FString& MissionScript)
{
	MissionScriptBorder->SetVisibility(ESlateVisibility::Visible);
	MissionScriptTextBlock->SetText(FText::FromString(MissionScript));
	PlayAnimation(MissionComplete);
}
