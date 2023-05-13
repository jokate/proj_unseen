// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/InteractionWidgetInterface.h"
#include "AstralBoxWidget.generated.h"

/**
 * 
 */

class UBoxUIDataAsset;

UCLASS()
class LUNARMODULARBASE_API UAstralBoxWidget : public UUserWidget, public IInteractionWidgetInterface
{
	GENERATED_BODY()
	
public:
	UAstralBoxWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicUIMaterialInstance;

	virtual void NativeConstruct() override;

private :
	UPROPERTY()
	TObjectPtr<UBoxUIDataAsset> BoxUIDataAsset;

	UPROPERTY()
	TObjectPtr<class UCanvasPanel> CanvasPanel;

	UPROPERTY()
	TObjectPtr<class UImage> PercentTargetImage;

	//User Activate Widget
protected :
	const float ActivateIncreasePercentage = 0.05f;
	const float CompletePercentage = 1.0f;
	float CurrentPercentage = 0.0f;

	FOnActivated OnActivated;

	FTimerHandle ActivationTimer;

	virtual void OnActivateButtonPressed() override;

	virtual FOnActivated& ActivatedEventBind() override;

	virtual void OnActivateButtonReleased() override;

	void SetPercentage(float InPercentage);

protected :
	virtual void OnPlayerTriggered(bool bIsTriggered) override;
};
