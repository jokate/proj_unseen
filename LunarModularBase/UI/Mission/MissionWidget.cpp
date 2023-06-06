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
	MissionDialogBorder->SetVisibility(ESlateVisibility::Hidden);
	MissionDialogBorder->OnMouseButtonDownEvent.BindUFunction(this, "DialogStringUpdate");
}

void UMissionWidget::UpdateMissionDialogWidget(const TArray<FString>& MissionDescription)
{
	if (!MissionDescription.IsEmpty()) {
		if (DialogString.IsEmpty()) {
			DialogString = MissionDescription;
			MissionDialogText->SetText(FText::FromString(DialogString[DialogIndex]));
			DialogIndex = FMath::Clamp(DialogIndex + 1, 0, DialogString.Num());
			MissionDialogBorder->SetVisibility(ESlateVisibility::Visible);
			AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
			CurrentActor->DisableInput(GetOwningPlayer());
			GetOwningPlayer()->bShowMouseCursor = true;
		}
		else
		{
			DialogString.Append(MissionDescription);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Mission Dialog Is Empty"));
		MissionTextBorder->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(MissionComplete);
	}
}

void UMissionWidget::UpdateMissionText(FString& MissionScript)
{
	MissionText->SetText(FText::FromString(MissionScript));
}

void UMissionWidget::ReactivateMissionTextBorder()
{
	MissionTextBorder->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(MissionComplete);
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
		MissionDialogBorder->SetVisibility(ESlateVisibility::Hidden);
		MissionTextBorder->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(MissionComplete);

		AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
		CurrentActor->EnableInput(GetOwningPlayer());
		GetOwningPlayer()->bShowMouseCursor = false;
		DialogString.Empty();
	}
}
