// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyGameMode.h"
#include "Player/AstroController.h"

ALobbyGameMode::ALobbyGameMode()
{

	static ConstructorHelpers::FClassFinder<APlayerController> CONTROLLER_CLASS(TEXT("'/Script/LunarModularBase.AstroController'"));
	if (CONTROLLER_CLASS.Succeeded()) {
		PlayerControllerClass = CONTROLLER_CLASS.Class;
	}
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AAstroController* Player = CastChecked<AAstroController>(NewPlayer);
	if (NumberOfPlayer % PlayerSide == 0) {
		Player->CurrentPlayerType = EPlayerType::PLAYER_FRONT;
		UE_LOG(LogTemp, Warning, TEXT("Frontward Set : %d"), NumberOfPlayer);
	}
	else {
		Player->CurrentPlayerType = EPlayerType::PLAYER_BACK;
		UE_LOG(LogTemp, Warning, TEXT("Backward Set %d"), NumberOfPlayer);
	}
	++NumberOfPlayer;
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayer;
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	bUseSeamlessTravel = true;
}
