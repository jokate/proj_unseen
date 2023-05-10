// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AstroDefinition.h"
#include "AstroMissionSingleton.generated.h"


/**
 * 
 */
DECLARE_DELEGATE_RetVal_OneParam(class UMission*, FOnCollabMissionChange, FString);

USTRUCT(BlueprintType)
struct	FCollabMissionDistributor {
	GENERATED_BODY()

	FCollabMissionDistributor() {}
	FCollabMissionDistributor(const FOnCollabMissionChange& InCollabMission) : CollabMissionDistributor(InCollabMission) {}

	FOnCollabMissionChange CollabMissionDistributor;
};
class UMission;

UCLASS()
class LUNARMODULARBASE_API UAstroMissionSingleton : public UObject
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	TObjectPtr<class UDataTable> MissionTable;

	UPROPERTY(VisibleAnywhere)
	TMap<FString, FMissionData> Missions;

	UPROPERTY()
	TMap<EPlayerType, FCollabMissionDistributor> CollabMissionDistributors;
public :

	UAstroMissionSingleton();
	
	static UAstroMissionSingleton& Get();

	UMission* GetMission(uint8 IsCurrentCollab, EPlayerType PlayerType, FString MissionID);

	UMission* AfterClearCollabFront(FString InMissionID);

	UMission* AfterClearCollabBack(FString InMissionID);

	FString ReturnMissionScript(FName InMissionID);

	FString ReturnMissionDescription(FName InMissionID);

};
