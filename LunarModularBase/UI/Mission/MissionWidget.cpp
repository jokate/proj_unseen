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
	MissionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MissionText")));
	MissionTextBorder = Cast<UBorder>(GetWidgetFromName(TEXT("MissionTextBorder")));
	MissionDialogBorder = Cast<UBorder>(GetWidgetFromName(TEXT("MissionDialogBorder")));
	MissionDialogText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MissionDialogText")));
	SetVisibility(ESlateVisibility::Hidden);
	MissionDialogBorder->OnMouseButtonDownEvent.BindUFunction(this, "DialogStringUpdate");
}

void UMissionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (MissionDialogBorder->GetVisibility() == ESlateVisibility::Visible)
		OnVisible();
}

void UMissionWidget::UpdateMissionDialogWidget(const TArray<FString>& MissionDescription)
{
	if (!MissionDescription.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("Mission Onboard"))
		DialogStringOnBoard(MissionDescription);
		bIsMissionDialog = true;
	}
	else
	{
		ReactivateMissionTextBorder();
	}
}

void UMissionWidget::UpdateMissionText(FString& MissionScript)
{
	MissionText->SetText(FText::FromString(MissionScript));
}

void UMissionWidget::ReactivateMissionTextBorder()
{
	SetVisibility(ESlateVisibility::Visible);
	MissionTextBorder->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(MissionComplete);
}

void UMissionWidget::DialogStringOnBoard(const TArray<FString>& MissionDescription)
{
	UE_LOG(LogTemp, Warning, TEXT("Dialog Onboard"))
	SetVisibility(ESlateVisibility::Visible);
	MissionDialogBorder->SetVisibility(ESlateVisibility::Visible);

	if (DialogString.IsEmpty()) {

		bIsMissionDialog = false;
		DialogString = MissionDescription;
		MissionDialogText->SetText(FText::FromString(DialogString[DialogIndex]));
		DialogIndex = FMath::Clamp(DialogIndex + 1, 0, DialogString.Num());
	}
	else
	{
		DialogString.Append(MissionDescription);
	}
}

void UMissionWidget::DialogStringUpdate()
{
	if (DialogIndex < DialogString.Num())
	{
		MissionDialogText->SetText(FText::FromString(DialogString[DialogIndex]));
		DialogIndex = FMath::Clamp(DialogIndex + 1, 0, DialogString.Num());
	}
	else
	{
		DialogIndex = 0;
		DialogString.Empty();
		MissionDialogBorder->SetVisibility(ESlateVisibility::Hidden);
		MissionTextBorder->SetVisibility(ESlateVisibility::Visible);

		if (bIsMissionDialog)
			PlayAnimation(MissionComplete);
		else 
		{
			SetVisibility(ESlateVisibility::Hidden);
		}

		OnInvisible();
	}
}

void UMissionWidget::OnVisible()
{
	SetVisibility(ESlateVisibility::Visible);
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->DisableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = true;
}

void UMissionWidget::OnInvisible()
{
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->EnableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = false;
}

void UMissionWidget::CheckIfAnotherDialogInit()
{
	if (DialogString.IsEmpty())
		SetVisibility(ESlateVisibility::Hidden);
}
