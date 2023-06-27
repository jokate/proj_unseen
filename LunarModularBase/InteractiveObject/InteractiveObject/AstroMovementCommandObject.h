// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "Interface/MovementCommandInterface.h"
#include "AstroMovementCommandObject.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroMovementCommandObject : public AAstroInteractableObject, public IMovementCommandInterface
{
	GENERATED_BODY()
	
public :

	AAstroMovementCommandObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	TObjectPtr<class UMovementCommandComponent> MovementCommandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AAstroTriggerResponseObject> NeedToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDirection, FVector> MovementVectors;

protected :
	virtual void SetPercentage(float Infloat) override;

	virtual void MoveObject(EDirection Direction) override;

	float Time = 0;

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnMovementStarted"))
	void K2_OnObjectMove(EDirection InVector);

	UPROPERTY()
	uint8 bIsCoolDown : 1;

	FTimerHandle MovementHandle;
};
