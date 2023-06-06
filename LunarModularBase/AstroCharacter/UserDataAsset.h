// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MovementDataAsset.h"
#include "InputMappingContext.h"
#include "UI/AstroPlayer/AstroCharacterWidget.h"

#include "UserDataAsset.generated.h"

/**
 *
 */
UCLASS()
class LUNARMODULARBASE_API UUserDataAsset : public UDataAsset
{
	GENERATED_BODY()


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TObjectPtr<UAstroCharacterWidget> UIAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TObjectPtr<USkeletalMesh> AstroMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UAnimInstance> AnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TObjectPtr<UInputMappingContext> InputMappingContextAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TObjectPtr<UMovementDataAsset> MovementDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float GravityScale = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float JumpZVelocity = 420.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float WalkSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float RunningSpeed = 400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FVector RelativeLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FRotator RelativeRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TObjectPtr<UAnimMontage> AnimMontage;
};
