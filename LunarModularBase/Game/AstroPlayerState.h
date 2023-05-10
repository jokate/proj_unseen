// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AstroDefinition.h"
#include "AstroPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public :
	AAstroPlayerState();


	void InitData(EPlayerType InPlayerType);

	EPlayerType GetPlayerType() { return PlayerType; }

	int32 GetPlayerHp() { return PlayerHp; }

	void HpMinus() { --PlayerHp; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(Replicated, VisibleAnywhere, meta = (PrivateAccess = "true"))
	EPlayerType PlayerType;

	UPROPERTY(Replicated, VisibleAnywhere, meta = (PrivateAccess = "true"))
	int32 PlayerHp;
	
	FTimerHandle HPTimer;
};
