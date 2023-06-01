// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroGameInstance.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

const static FName SESSION_NAME = TEXT("Game");

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
		}
	}
	
}

void UAstroGameInstance::HostGameSession(FString String)
{
	const int MaxNumofPlayer = 2;
	FOnlineSessionSettings OnlineSessionSettings;
	OnlineSessionSettings.bAllowJoinInProgress = true;
	OnlineSessionSettings.bAllowJoinViaPresence = true;
	OnlineSessionSettings.NumPublicConnections = 2;
	OnlineSessionSettings.bUsesPresence = true;
	OnlineSessionSettings.bShouldAdvertise = true;
	OnlineSessionSettings.bIsDedicated = false;
	OnlineSessionSettings.bIsLANMatch = (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL") ? false : true;


	FOnlineSessionSetting SessionName;
	SessionName.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
	SessionName.Data = String;
	OnlineSessionSettings.Settings.Add("SESSION_NAME", SessionName);

	SessionInterface->CreateSession(0, SESSION_NAME, OnlineSessionSettings);
}

void UAstroGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)

{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSession Complete, Succeeded : %d"), Succeeded);
	if (Succeeded)
	{
		SessionInterface->UpdateSession(SessionName, SessionInterface->GetNamedSession(SessionName)->SessionSettings);
		GetWorld()->ServerTravel("/Game/Level/LobbyScene?listen");
	}
}


void UAstroGameInstance::JoinGameSession(FResultConstructor Result)
{
	SessionInterface->JoinSession(0, SESSION_NAME, 	Result.Result);
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
				PlayerController->ClientTravel(JointAddress, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}

void UAstroGameInstance::FindGameSession()
{
	LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
	LastSessionSearch->MaxSearchResults = 100;
	LastSessionSearch->bIsLanQuery = (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL");
	LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionInterface->FindSessions(0, LastSessionSearch.ToSharedRef());
	
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
		SessionInterface->UpdateSession(SessionName, SessionInterface->GetNamedSession(SessionName)->SessionSettings);
		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController) {

			PlayerController->ClientTravel("/Game/Level/MainScene", ETravelType::TRAVEL_Absolute);
		}
	}
}

void UAstroGameInstance::StartSession()
{
	if (SessionInterface) 
	{
		SessionInterface->StartSession(SESSION_NAME);
	}
}

void UAstroGameInstance::OnStartGameSessionCompleted(FName SessionName, bool Succeeded)
{
	if (Succeeded)
	{
		APlayerController* PlayerController = GetFirstLocalPlayerController();
		GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/NewWorld?listen");
	}
}



