// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroPlayerState.h"
#include "Net/UnrealNetwork.h"

AAstroPlayerState::AAstroPlayerState()
{
	PlayerType = EPlayerType::PLAYER_NONE;
	PlayerHp = 100;
	bReplicates = true;
}

void AAstroPlayerState::InitData(EPlayerType InPlayerType)
{
	PlayerType = InPlayerType;

	GetWorld()->GetTimerManager().SetTimer(HPTimer, [&]() {
		--PlayerHp;
	}, 20.0f, true);


}

void AAstroPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAstroPlayerState, PlayerType);
	DOREPLIFETIME(AAstroPlayerState, PlayerHp);
}

