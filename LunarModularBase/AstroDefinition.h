// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "AstroDefinition.generated.h"

#define ASTRO_FRONT_ID TEXT("F_")
#define ASTRO_BACK_ID TEXT("B_")
#define ASTRO_COOP_ID TEXT("C_")
UENUM(BlueprintType)
enum class EMissionType : uint8 {
	MISSION_INTERACTION,
	MISSION_WAIT,
	MISSION_PUZZLE,
	MISSION_SHARED
};

USTRUCT(BlueprintType)
struct FMissionData : public FTableRowBase
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName MissionID = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EMissionType MissionType = EMissionType::MISSION_INTERACTION;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString MissionDesc = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName NextMissionID = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName MissionItemID = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString MissionScript = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName NeedToClear = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ActCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	uint8 bIsSharedGoal = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName AfterSharedFront = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName AfterSharedBack = "";
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
