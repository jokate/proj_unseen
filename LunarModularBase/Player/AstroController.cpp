// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AstroController.h"
#include "Game/AstroPlayerState.h"
#include "Lobby/LobbyGameMode.h"
#include "Game/AstroGameInstance.h"
#include "Interface/AstroCharacterInterface.h"
#include "Net/UnrealNetwork.h"


AAstroController::AAstroController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentPlayerType = EPlayerType::PLAYER_NONE;
	bReplicates = true;
}

void AAstroController::ReverseType()
{
	CurrentPlayerType = (CurrentPlayerType == EPlayerType::PLAYER_FRONT) ? EPlayerType::PLAYER_BACK : EPlayerType::PLAYER_FRONT;
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

void AAstroController::OnNetCleanup(UNetConnection* Connection)
{
	if (HasAuthority()) 
	{
		ALobbyGameMode* GameMode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
		if(GameMode) 
		{
			GameMode->LogOutProcess(this);
			if (this->CurrentPlayerType == EPlayerType::PLAYER_FRONT)
				GameMode->FrontwardCount.fetch_sub(1);
			else
			{
				GameMode->BackwardCount.fetch_sub(1);
			}
		}

	}
	Super::OnNetCleanup(Connection);
}

void AAstroController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAstroController, CurrentPlayerType);
}

void AAstroController::UpdatedType()
{
	auto AstroGameInstance = CastChecked<UAstroGameInstance>(GetGameInstance());
	AstroGameInstance->OnPlayerTypeChanged();
}





