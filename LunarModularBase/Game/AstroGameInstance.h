// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "AstroGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FResultConstructor
{
	GENERATED_BODY()
	
	FResultConstructor() {};
	FResultConstructor(int32 InPing, FString InOwner, int32 InCurrentPlayer, int32 InMaxPlayer, FOnlineSessionSearchResult InResult) : PingMs(InPing), OwningUserName(InOwner)
		, CurrentPlayer(InCurrentPlayer), MaxPlayer(InMaxPlayer), Result(InResult) {};

public :
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Data)
	int32 PingMs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString OwningUserName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 CurrentPlayer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Data)
	int32 MaxPlayer;

	FOnlineSessionSearchResult Result;

};

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	
	virtual void Init() override;

	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	IOnlineSessionPtr SessionInterface;

	UFUNCTION(BlueprintCallable)
	void HostGameSession(FString InString);

	UFUNCTION(BlueprintCallable)
	void JoinGameSession(FResultConstructor Result);

	UFUNCTION(BlueprintCallable)
	void FindGameSession();

	UFUNCTION(BlueprintCallable)
	void DestroySession(FName SessionName);

	UFUNCTION(BlueprintCallable)
	void StartSession();

	virtual void OnDestroySessionComplete(FName SessionName, bool Succeeded);

	UPROPERTY(BlueprintReadWrite)
	FName CurrentRoomName;
	
public :
	virtual void OnCreateSessionComplete(FName SessionName, bool Succeeded);

	void OnJoinGameSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnFindSessionsComplete(bool Succeeded);

	void OnStartGameSessionCompleted(FName SessionName, bool Succeeded);

public :
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnFindCompletedCPP"))
	void K2_FindCompleted(const TArray<FResultConstructor>& FoundResults);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnCharacterCountChangedCPP"))
	void K2_OnPlayerChanged(int32 CurrentPlayer);


public:
	UFUNCTION(BlueprintCallable)
	bool IsThisPlayerHostInThisSession();

	uint8 bIsHost : 1;

	UFUNCTION(BlueprintCallable)
	void ReverseTypeOfPlayer();

};
