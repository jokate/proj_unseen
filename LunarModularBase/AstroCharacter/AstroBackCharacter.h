// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AstroCharacter/AstroCharacter.h"
#include "AstroBackCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroBackCharacter : public AAstroCharacter
{
	GENERATED_BODY()
	
public :
	AAstroBackCharacter();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	FORCEINLINE virtual EPlayerType ReturnTag() override { return EPlayerType::PLAYER_BACK; }
	virtual void Req_MissionClear(FName ObjectName) override;
	virtual void TakeItem(UAstroItemData* InItemData) override;

	virtual void OnObjectCollided(FOnActivatedComplete& InActivaedDelegate, FOnTakeItemDelegate& InTakeItemDelegate) override;
};
