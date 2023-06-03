// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyGameMode.h"
#include "Player/AstroController.h"
#include "OnlineSubsystemUtils.h"
#include "AstroDefinition.h"
#include "Game/AstroGameInstance.h"
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
	if (FrontwardCount <= BackwardCount) {
		Player->CurrentPlayerType = EPlayerType::PLAYER_FRONT;
		FrontwardCount.fetch_add(1);
	}
	else {
		Player->CurrentPlayerType = EPlayerType::PLAYER_BACK;
		BackwardCount.fetch_add(1);
	}

	FUniqueNetIdRepl UniqueNetIdRepl;
	if (NewPlayer->IsLocalPlayerController())
	{
		ULocalPlayer* LocalPlayer = NewPlayer->GetLocalPlayer();
		if (IsValid(LocalPlayer))
		{
			UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
		}
		else
		{
			UNetConnection* RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
			check(IsValid(RemoteNetConnection));
			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
		}
	}
	else
	{
		UNetConnection* RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
		check(IsValid(RemoteNetConnection));
		UniqueNetIdRepl = RemoteNetConnection->PlayerId;
	}

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(NewPlayer->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (Session->RegisterPlayer(SESSION_NAME, *UniqueNetIdRepl, false)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("LOGIN COMPLETED"))
	}

	auto AstroGameInstance = CastChecked<UAstroGameInstance>(GetGameInstance());
	PlayerControllers.Add(Player);
	UE_LOG(LogTemp, Warning, TEXT("PlayerCount = %d"), PlayerControllers.Num())
	AstroGameInstance->K2_OnPlayerChanged(PlayerControllers.Num());
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::LogOutProcess(APlayerController* ExitPlayer)
{

	FUniqueNetIdRepl UniqueNetIdRepl;
	AAstroController* Player = CastChecked<AAstroController>(ExitPlayer);
	if (ExitPlayer->IsLocalPlayerController())
	{
		ULocalPlayer* LocalPlayer = ExitPlayer->GetLocalPlayer();
		if (IsValid(LocalPlayer))
		{
			UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
		}
		else
		{
			UNetConnection* RemoteNetConnection = Cast<UNetConnection>(ExitPlayer->Player);
			check(IsValid(RemoteNetConnection));
			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
		}
	}
	else
	{
		UNetConnection* RemoteNetConnection = Cast<UNetConnection>(ExitPlayer->Player);
		check(IsValid(RemoteNetConnection));
		UniqueNetIdRepl = RemoteNetConnection->PlayerId;
	}

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(ExitPlayer->GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (Session->UnregisterPlayer(SESSION_NAME, *UniqueNetIdRepl))
	{
		UE_LOG(LogTemp, Warning, TEXT("LOGOUT COMPLETED"))
	}
	auto AstroGameInstance = CastChecked<UAstroGameInstance>(GetGameInstance());
	PlayerControllers.Remove(Player);
	AstroGameInstance->K2_OnPlayerChanged(PlayerControllers.Num());
}

void ALobbyGameMode::ChangePlayerType()
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AAstroController* PlayerController = Cast<AAstroController>(It->Get());
		if (PlayerController)
		{
			if (PlayerController->CurrentPlayerType == EPlayerType::PLAYER_FRONT)
			{
				FrontwardCount.fetch_sub(1);
				BackwardCount.fetch_add(1);
			}
			else {
				BackwardCount.fetch_sub(1);
				FrontwardCount.fetch_add(1);
			}
			PlayerController->ReverseType();
		}
	}
}
