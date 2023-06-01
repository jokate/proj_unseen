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
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FUserInfo> UserInfos;

public :
	UPROPERTY(BlueprintReadWrite, Meta = (PrivateAccess = true))
	int32 NumberOfPlayer = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerSide = 2;

	UPROPERTY()
	TObjectPtr<class UAstroClassDataSet> ClassDataAsset;
};
