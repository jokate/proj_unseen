// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroGameInstance.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"
#include "AstroDefinition.h"
#include "Lobby/LobbyGameMode.h"
#include "Player/AstroController.h"

void UAstroGameInstance::Init()
{
	Super::Init();

	if(IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get()) 
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UAstroGameInstance::OnCreateSessionComplete);
			SessionInterface->OnStartSessionCompleteDelegates.AddUObject(this, &UAstroGameInstance::OnStartGameSessionCompleted);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UAstroGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UAstroGameInstance::OnJoinGameSessionCompleted);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UAstroGameInstance::OnDestroySessionComplete);
			SessionInterface->OnEndSessionCompleteDelegates.AddUObject(this, &UAstroGameInstance::OnEndSessionComplete);
			GetEngine()->OnNetworkFailure().AddUObject(this, &UAstroGameInstance::HandleNetworkFailure);
			bIsHost = false;
		}
	}
	
}

void UAstroGameInstance::HostGameSession(FString String)
{
	const int MaxNumofPlayer = 2;
	FOnlineSessionSettings OnlineSessionSettings;
	OnlineSessionSettings.bAllowJoinInProgress = true;
	OnlineSessionSettings.bAllowInvites = true;
	OnlineSessionSettings.bAllowJoinViaPresence = true;
	OnlineSessionSettings.NumPublicConnections = 2;
	OnlineSessionSettings.bUsesPresence = true;
	OnlineSessionSettings.bShouldAdvertise = true;
	OnlineSessionSettings.bUseLobbiesIfAvailable = true;
	OnlineSessionSettings.bIsDedicated = false;
	OnlineSessionSettings.bIsLANMatch = (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL") ? false : true;


	FOnlineSessionSetting SessionName;
	SessionName.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
	SessionName.Data = String;
	OnlineSessionSettings.Settings.Add("SESSION_NAME", SessionName);
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), SESSION_NAME, OnlineSessionSettings);
}

void UAstroGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSession Complete, Succeeded : %d"), Succeeded);
	if (Succeeded)
	{
		CurrentRoomName = SessionName;
		SessionInterface->UpdateSession(SessionName, SessionInterface->GetNamedSession(SessionName)->SessionSettings);
		bIsHost = true;
		GetWorld()->ServerTravel("/Game/Level/LobbyScene?listen");
	}
}


void UAstroGameInstance::JoinGameSession(FResultConstructor Result)
{
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), SESSION_NAME, 	Result.Result);
}

void UAstroGameInstance::OnJoinGameSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success) {
		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController) {
			FString JointAddress = "";
			SessionInterface->UpdateSession(SessionName, SessionInterface->GetNamedSession(SessionName)->SessionSettings);
			SessionInterface->GetResolvedConnectString(SessionName, JointAddress);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *JointAddress);
			if (JointAddress != "")
			{
				CurrentRoomName = SessionName;
				PlayerController->ClientTravel(JointAddress, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}

void UAstroGameInstance::FindGameSession()
{
	LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
	LastSessionSearch->MaxSearchResults = 200000;
	LastSessionSearch->bIsLanQuery = (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL");
	LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef());
}

void UAstroGameInstance::OnFindSessionsComplete(bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("FindSession Complete, Succedced : %d"), Succeeded);
	if(Succeeded) 
	{
		if (LastSessionSearch.IsValid()) {
			TArray<FOnlineSessionSearchResult> SearchResults = LastSessionSearch->SearchResults;
			TArray<FResultConstructor> Constructors;
			UE_LOG(LogTemp, Warning, TEXT("SearchResults, ServerCount : %d"), SearchResults.Num());
			for (auto SearchResult : SearchResults)
			{
				Constructors.Add(FResultConstructor(SearchResult.PingInMs, 
					SearchResult.Session.SessionSettings.Settings.FindRef("SESSION_NAME").Data.ToString(),
					SearchResult.Session.SessionSettings.NumPublicConnections - SearchResult.Session.NumOpenPublicConnections,
					SearchResult.Session.SessionSettings.NumPublicConnections, SearchResult));
			}
			K2_FindCompleted(Constructors);
		}
	}

}

void UAstroGameInstance::DestroySession(FName SessionName)
{
	SessionInterface->DestroySession(SESSION_NAME);
}

void UAstroGameInstance::OnDestroySessionComplete(FName SessionName, bool Succeeded)
{
	if(Succeeded) 
	{
		CurrentRoomName = "";
		SessionInterface->UpdateSession(SessionName, SessionInterface->GetNamedSession(SessionName)->SessionSettings);
		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController) {
			PlayerController->ClientTravel("/Game/Level/MainScene", ETravelType::TRAVEL_Absolute);
			bIsHost = false;
		}
	}
}

void UAstroGameInstance::OnEndSessionComplete(FName SessionName, bool Succeeded)
{
	if(Succeeded) 
	{
		DestroySession(SessionName);
	}
}

//When Session Has an Error or Session Host Leave th
void UAstroGameInstance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogTemp, Warning, TEXT("Host Ended Or Session Has An Error"));
	SessionInterface->DestroySession(SESSION_NAME);
}

void UAstroGameInstance::StartSession()
{
	if (SessionInterface) 
	{
		SessionInterface->StartSession(SESSION_NAME);
	}
}

void UAstroGameInstance::EndSession()
{
	if(SessionInterface) 
	{
		SessionInterface->EndSession(SESSION_NAME);
	}
}


void UAstroGameInstance::OnStartGameSessionCompleted(FName SessionName, bool Succeeded)
{
	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/NewWorld?listen");
	}
}

bool UAstroGameInstance::IsThisPlayerHostInThisSession()
{
	return bIsHost;
}

void UAstroGameInstance::ReverseTypeOfPlayer()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController->GetLocalRole() == ENetRole::ROLE_Authority) 
	{
		auto LobbyGameMode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
		LobbyGameMode->ChangePlayerType();
	}
}

void UAstroGameInstance::OnPlayerUpdated(const TSet<AAstroController*>& Controllers)
{
	K2_OnPlayerUpdateTriggered();
	for(auto Controller : Controllers) 
	{
		K2_OnPlayerUpdated(Controller);
	}
}

void UAstroGameInstance::OnPlayerTypeChanged()
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It) 
	{
		auto AstroController = CastChecked<AAstroController>(It->Get());
		K2_OnPlayerUpdated(AstroController);
	}
}




