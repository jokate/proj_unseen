// Fill out our copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/AstroMissionManager.h"
#include "Engine/StreamableManager.h"
#include "AstroGameMode.generated.h"
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

	virtual void InMissionIDEventOccured(FName InID) override;
public :

	UPROPERTY(BlueprintReadWrite, Meta = (PrivateAccess = true))
	int32 NumberOfPlayer = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerSide = 2;

	UPROPERTY()
	TObjectPtr<class UMissionManagementComponent> MissionManager;

private :
	UPROPERTY()
	TObjectPtr<class UAstroClassDataSet> ClassDataAsset;

};
