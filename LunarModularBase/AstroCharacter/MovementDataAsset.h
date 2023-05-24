// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "MovementDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UMovementDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSearch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputExplore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputTurn;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* ItemUse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* ItemInstall;
	
};
