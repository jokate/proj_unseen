// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionWidget.generated.h"

/**
 *
 */
UCLASS()
class LUNARMODULARBASE_API UMissionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMissionWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateMissionDialogWidget(const TArray<FString>& MissionDescription);

	void UpdateMissionText(FString& MissionScript);

	void ReactivateMissionTextBorder();

	void DialogStringOnBoard(const TArray<FString>& MissionDescription);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> DialogString;

	UFUNCTION(BlueprintCallable)
		void DialogStringUpdate();

	int32 DialogIndex = 0;

	uint8 bIsMissionDialog = 0;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UTextBlock> MissionText;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UBorder> MissionTextBorder;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UTextBlock> MissionDialogText;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UBorder> MissionDialogBorder;

private:

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		TObjectPtr<UWidgetAnimation> MissionComplete;
};
