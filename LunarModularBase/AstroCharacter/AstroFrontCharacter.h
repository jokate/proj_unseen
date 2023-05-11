// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AstroCharacter/AstroCharacter.h"
#include "AstroFrontCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroFrontCharacter : public AAstroCharacter
{
	GENERATED_BODY()
	
	
public :
	AAstroFrontCharacter();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Req_MissionClear(FName ObjectName);

	FORCEINLINE virtual EPlayerType ReturnTag() override { return EPlayerType::PLAYER_FRONT; }

	virtual void TakeItem(UAstroItemData* InItemData) override;

	virtual void OnObjectCollided(FOnActivatedComplete& InActivaedDelegate, FOnTakeItemDelegate& InTakeItemDelegate) override;
};
