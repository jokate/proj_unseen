// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AstroItemInterface.generated.h"

// This class does not need to be modified.

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UAstroItemData*);
class UAstroActiveItemData;
UINTERFACE(MinimalAPI)
class UAstroItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUNARMODULARBASE_API IAstroItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void UseItem(UAstroItemData* InItemData) = 0;

	virtual bool ContainsItem(UAstroItemData* ItemData) = 0;

	virtual void OnItemObjectCollided(FOnTakeItemDelegate& ItemDelegate) = 0;

	virtual void ItemEquip(UAstroActiveItemData* InItemData) = 0;

	virtual void ItemDeEquip(bool CanDequip) = 0;
};
