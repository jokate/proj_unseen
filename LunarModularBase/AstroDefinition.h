// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "AstroDefinition.generated.h"


const static FName SESSION_NAME = TEXT("Game");

#define ASTRO_FRONT_ID TEXT("F_")
#define ASTRO_BACK_ID TEXT("B_")
#define ASTRO_COOP_ID TEXT("C_")

UENUM(BlueprintType)
enum class EDirection : uint8 
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

UENUM(BlueprintType)
enum class EMissionType : uint8 {
	MISSION_INTERACTION,
	MISSION_WAIT,
	MISSION_PUZZLE,
	MISSION_SHARED
};

UENUM(BlueprintType)
enum class EInteractiveType : uint8
{
	NORMAL,
	TIMELIMIT,
	SEQUENTIAL
};

USTRUCT(BlueprintType)
struct FMissionData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EMissionType MissionType = EMissionType::MISSION_INTERACTION;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString MissionDesc = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FName NextMissionID = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FString> MissionScripts;

};

USTRUCT(BlueprintType)
struct FInteractiveMissionData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EInteractiveType InteractionType = EInteractiveType::NORMAL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FName> MissionItemIDs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 ActCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Time = 0;
};


USTRUCT(BlueprintType)
struct FWaitMissionData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FName NeedToClear = "";
};


UENUM(BlueprintType)
enum class EPlayerType : uint8 {
	PLAYER_NONE = 0,
	PLAYER_BACK = 1,
	PLAYER_FRONT = 2,
};

/**
 *
 */
UCLASS()
class LUNARMODULARBASE_API UAstroDefinition : public UObject
{
	GENERATED_BODY()

};
