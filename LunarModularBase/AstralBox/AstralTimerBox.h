// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AstralBox/AstralBox.h"
#include "AstralTimerBox.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstralTimerBox : public AAstralBox
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReActivateTimer)
	float ReactivateTime = 0.0f;

protected :
	virtual void SetObjActiveComplete() override;

	
};
