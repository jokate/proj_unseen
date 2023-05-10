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
	
public :
	UMissionWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	void UpdateMissionWidget(FString& MissionDescription);

	void UpdateMissionScript(FString& MissionScript);


	UPROPERTY()
	TObjectPtr<class UTextBlock> MissionTextBlock;

	UPROPERTY()
	TObjectPtr<class UBorder> MissionBorder;

	UPROPERTY()
	TObjectPtr<class UTextBlock> MissionScriptTextBlock;

	UPROPERTY()
	TObjectPtr<class UBorder> MissionScriptBorder;

private:

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> MissionComplete;
};
