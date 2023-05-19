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
class LUNARMODULARBASE_API UAstralBoxWidget : public UUserWidget
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

	UFUNCTION(BlueprintCallable, Category = UISet)
	void SetPercentage(float InPercentage);

protected :
	UFUNCTION(BlueprintCallable, Category = UISet)
	void OnPlayerTriggered(bool bIsTriggered);
};
