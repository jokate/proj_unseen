// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AstroItemData.h"

void UAstroItemData::BeginDestroy()
{
	Super::BeginDestroy();
	ItemCount = 1;
}
