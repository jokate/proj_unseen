// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AstroDefinition.h"
#include "AstroMissionSingleton.generated.h"


/**
 *
 */
DECLARE_DELEGATE_RetVal_OneParam(class UAstroMissionBase*, FOnMissionChanged, FName);

USTRUCT(BlueprintType)
struct	FMissionGenerator {
	GENERATED_BODY()

		FMissionGenerator() {}
	FMissionGenerator(const FOnMissionChanged& InMissionChangeEvent) : MissionChange(InMissionChangeEvent) {}

	FOnMissionChanged MissionChange;
};
class UMission;
class UAstroMissionBase;

UCLASS()
class LUNARMODULARBASE_API UAstroMissionSingleton : public UObject
{
	GENERATED_BODY()

		//DataTables
protected:

	UPROPERTY()
		TObjectPtr<class UDataTable> MissionTable;

	UPROPERTY()
		TObjectPtr<class UDataTable> InteractiveMissionDatabase;

	UPROPERTY()
		TObjectPtr<class UDataTable> WaitMissionDatabase;

	UPROPERTY(VisibleAnywhere)
		TMap<FName, FMissionData> Missions;

	UPROPERTY(VisibleAnywhere)
		TMap<FName, FInteractiveMissionData> InteractiveMissionData;

	UPROPERTY(VisibleAnywhere)
		TMap<FName, FWaitMissionData> WaitMissionData;

public:
	TMap<EMissionType, FMissionGenerator> MissionGenerator;

	UAstroMissionBase* InteractiveMissionReturn(FName InMissionID);

	UAstroMissionBase* WaitMissionReturn(FName InMissionID);

public:

	UAstroMissionSingleton();

	static UAstroMissionSingleton& Get();

	UAstroMissionBase* GetMission(FName MissionID);

	TArray<FString> ReturnMissionScript(FName InMissionID);

	FString ReturnMissionDescription(FName InMissionID);

};
