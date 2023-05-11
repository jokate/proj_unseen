// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */

class UButton;
class UImage;
class UItemActivationWidget;


UCLASS()
class LUNARMODULARBASE_API UInventorySlotWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public :
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UItemActivationWidget> ItemActivationWidget;

	UPROPERTY()
	TObjectPtr<class UAstroItemData> ItemData;

	//Base Function
public :
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;



protected :
	UFUNCTION()
	void OnPressedItemButton();

	UFUNCTION()
	void OnActivationItemButton();

	UFUNCTION()
	void OnHoveredItemButton();
};
