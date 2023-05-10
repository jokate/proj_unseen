// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/WidgetInterface.h"
#include "Interface/InteractionWidgetInterface.h"
#include "AstralBoxWidget.generated.h"

/**
 * 
 */

class UBoxUIDataAsset;


UCLASS()
class LUNARMODULARBASE_API UAstralBoxWidget : public UUserWidget, public IWidgetInterface, public IInteractionWidgetInterface
{
	GENERATED_BODY()
	
public:
	UAstralBoxWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	TObjectPtr<UMaterialInstanceDynamic> DynamicUIMaterialInstance;

	virtual void NativeConstruct() override;

	virtual void PercentSet(OnActivate& Activated) override;

	virtual void VisibilitySet(OnVisible& VisibleFunc) override;

	void SetPercentage(float Percentage);

	void UpdateVisible(bool InBoolean);

private :
	UPROPERTY()
	TObjectPtr<UBoxUIDataAsset> BoxUIDataAsset;

	UPROPERTY()
	TObjectPtr<class UCanvasPanel> CanvasPanel;

	UPROPERTY()
	TObjectPtr<class UImage> PercentTargetImage;
};
