// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FUserInfo {
	GENERATED_BODY()
	
	FUserInfo() {};

	FUserInfo(FString InName) : Name(InName) {}
	
	FString Name;
	
};

UCLASS()
class LUNARMODULARBASE_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public :
	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	void LogOutProcess(APlayerController* ExitPlayer);

	void ChangePlayerType();
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FUserInfo> UserInfos;

public :

	UPROPERTY()
	TObjectPtr<class UAstroClassDataSet> ClassDataAsset;

	std::atomic<int32> BackwardCount = 0;

	std::atomic<int32> FrontwardCount = 0;

	UPROPERTY(BlueprintReadWrite)
	TSet<class AAstroController*> PlayerControllers;


};
