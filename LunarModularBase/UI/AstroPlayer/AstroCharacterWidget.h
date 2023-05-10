// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AstroCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HPTextUpdate(uint32& InHp);

	void ExploreUIActive(bool& Inboolean);


private: 

	UPROPERTY()
	TObjectPtr<class UTextBlock> HPTextBlock;

	UPROPERTY()
	TObjectPtr<class UCanvasPanel> ExploreCanvas;
};
