// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroTriggerResponseObject.h"
#include "AstroTriggerMoveResponseObject.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroTriggerMoveResponseObject : public AAstroTriggerResponseObject
{
	GENERATED_BODY()
	
public :
	AAstroTriggerMoveResponseObject();

	virtual void SetObjActiveComplete() override;

	virtual void SetObjDeActivateComplete() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveRate)
	float MoveRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveSpeed)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialPos)
	FVector InitialPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetPos)
	FVector TargetPos;

	UPROPERTY(BlueprintReadWrite, Category = NeedToReverse)
	uint8 NeedToRev : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = LerpingPoint)
	float LerpingPoint = 0.0f;
	
	void MoveObject();

	FTimerHandle ActivationHandle;
};
