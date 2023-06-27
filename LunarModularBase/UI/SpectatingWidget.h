// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpectatingWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API USpectatingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	USpectatingWidget(const FObjectInitializer& Initializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> SpectatingView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> FrontMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> BackMat;

	void VisibilityButtonPressed();
	
};
