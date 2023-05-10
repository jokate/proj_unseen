// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/AstroMissionManager.h"
#include "Engine/StreamableManager.h"
#include "AstroGameMode.generated.h"


/**
 *
 */


DECLARE_MULTICAST_DELEGATE_OneParam(FMissionClearCheckerDelegate, FName)
DECLARE_MULTICAST_DELEGATE(FOnMissionUpdateEventDelegate)

UCLASS()
class LUNARMODULARBASE_API AAstroGameMode : public AGameModeBase, public IAstroMissionManager
{
	GENERATED_BODY()
public:
	AAstroGameMode();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
public  :

	UPROPERTY(BlueprintReadWrite, Meta = (PrivateAccess = true))
	int32 NumberOfPlayer = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerSide = 2;

private :
	UPROPERTY()
	TObjectPtr<class UAstroClassDataSet> ClassDataAsset;

	//Current Missions
private :

	UPROPERTY()
	TObjectPtr<class UMission> FrontwardMission;

	UPROPERTY()
	TObjectPtr<class UMission> BackwardMission;

	UPROPERTY()
	TArray<FName> ClearedMissionList;


	//Mission Clear Check Functions
protected:
	//BroadCast Delegate
	FMissionClearCheckerDelegate MissionClearChecker;

	virtual void InMissionIDEventOccured(FName InID) override;

	void FrontwardMissionClearChecker(FName InID);

	void FrontwardMissionSetter();

	void BackwardMissionClearChecker(FName InID);

	void BackwardMissionSetter();
	
	//When Mission is cleared this function will called.
	void MissionClearedEvent(FName InID);

	//On Update
protected :
	//If Mission is updated, Check whether the Waiting Mission is Completed.
	FOnMissionUpdateEventDelegate MissionUpdateEvent;

	void IsFrontWaitMissionCleared();

	void IsBackWaitMissionCleared();
};
