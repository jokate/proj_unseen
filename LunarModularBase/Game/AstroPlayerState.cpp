// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroPlayerState.h"
#include "Net/UnrealNetwork.h"

AAstroPlayerState::AAstroPlayerState()
{
	PlayerType = EPlayerType::PLAYER_NONE;
	bReplicates = true;
}

void AAstroPlayerState::InitData(EPlayerType InPlayerType)
{
	PlayerType = InPlayerType;



}

void AAstroPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAstroPlayerState, PlayerType);
}

