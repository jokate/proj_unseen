// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemActivationWidget.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;

UCLASS()
class LUNARMODULARBASE_API UItemActivationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ItemActionButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemActionText;

	void SetItemActivateWidgetActive();
	
	void ButtonSet(bool bIsItemActive);

	UPROPERTY()
	TMap<uint8, FString> ActivationString;
	

};
