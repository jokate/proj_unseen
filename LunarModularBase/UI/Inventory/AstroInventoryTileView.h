// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TileView.h"
#include "AstroInventoryTileView.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroInventoryTileView : public UTileView
{
	GENERATED_BODY()
	
public :
	UAstroInventoryTileView(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

	void UpdateItem(UObject* Item);
};
