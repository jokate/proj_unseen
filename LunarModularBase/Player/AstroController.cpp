// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AstroController.h"
#include "Game/AstroPlayerState.h"
#include "Interface/AstroCharacterInterface.h"
#include "Net/UnrealNetwork.h"


AAstroController::AAstroController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentPlayerType = EPlayerType::PLAYER_NONE;
}


void AAstroController::BeginPlay()
{
	Super::BeginPlay();
}

void AAstroController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAstroController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

void AAstroController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}



