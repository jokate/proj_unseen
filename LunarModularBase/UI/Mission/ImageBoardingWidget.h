// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/AstroWidgetInterface.h"
#include "ImageBoardingWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UImageBoardingWidget : public UUserWidget, public IAstroWidgetInterface
{
	GENERATED_BODY()
	
	
public :

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ObjectSendImage;

	void ImageWidgetOnBoard(UTexture2D* InTexture);

	UFUNCTION(BlueprintCallable)
	void ImageWidgetUnBoard();


	UFUNCTION(BlueprintCallable)
	virtual void OnVisible() override;

	virtual void OnInvisible() override;

};
