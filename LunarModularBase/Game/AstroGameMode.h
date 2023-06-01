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
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;

	virtual void InMissionIDEventOccured(FName InID) override;
public :


	UPROPERTY()
	TObjectPtr<class UMissionManagementComponent> MissionManager;

private :
	UPROPERTY()
	TObjectPtr<class UAstroClassDataSet> ClassDataAsset;

};
