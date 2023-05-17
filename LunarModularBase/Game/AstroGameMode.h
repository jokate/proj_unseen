// Fill out our copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/AstroMissionManager.h"
#include "Engine/StreamableManager.h"
#include "AstroGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMissionClearCheckerDelegate, FName);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnMissionClearCheck, class UAstroMissionBase*, FName);


USTRUCT(BlueprintType)
struct FMissionChecker {

	GENERATED_BODY()

	FMissionChecker() {}

	FMissionChecker(const FOnMissionClearCheck& InMissionClearChecker) : MissionClearCheck(InMissionClearChecker) {}

	FOnMissionClearCheck MissionClearCheck;

};

/**
 *
 */

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

	//Mission Clear Check Functions
protected:
	virtual void InMissionIDEventOccured(FName InID) override;

private:

	UPROPERTY()
	TObjectPtr<class UAstroMissionBase> FrontwardMission;

	UPROPERTY()
	TObjectPtr<class UAstroMissionBase> BackwardMission;

	UPROPERTY()
	TArray<FName> MissionClearedList;

	//Mission Clear Check Functions

protected:
	//BroadCast Delegate
	FMissionClearCheckerDelegate MissionClearChecker;

	void FrontwardMissionClearChecker(FName InID);

	void FrontwardMissionSetter();

	void FrontwardGameStateSetter();

	void BackwardMissionClearChecker(FName InID);

	void BackwardMissionSetter();

	void BackwardGameStateSetter();

	//When Mission is cleared this function will called.
	void MissionClearedEvent(FName InID);

	FTimer TimerHandle;

	//Mission Clear Delegate
protected:
	UPROPERTY()
	TMap<EMissionType, FMissionChecker> MissionClearCheckEvent;

	bool InteractiveMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID);

	bool WaitMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID);

};
