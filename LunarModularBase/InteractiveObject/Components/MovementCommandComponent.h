// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/MovementCommandInterface.h"
#include "MovementCommandComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementStarted, EDirection, Direction);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UMovementCommandComponent : public UActorComponent, public IMovementCommandInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementCommandComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AAstroTriggerResponseObject> NeedToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDirection, FVector> MovementVectors;

	UFUNCTION(BlueprintCallable)
	void MovementCommandActivated();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnMovementStarted MovementStarted;

	UPROPERTY()
	uint8 bIsCoolDown : 1;
	FTimerHandle MovementHandle;

	virtual void MoveObject(EDirection Direction) override;
};
