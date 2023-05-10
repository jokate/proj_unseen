// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AstroDefinition.h"
#include "Mission.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_RetVal_OneParam(bool, FOnMissionClearDelegate, FName);

USTRUCT(BlueprintType)
struct FMissionClearWrapper {
	GENERATED_BODY()

	FMissionClearWrapper() {}
	FMissionClearWrapper(const FOnMissionClearDelegate& InMissionClearDelegate) : MissionClearDeleagate(InMissionClearDelegate) {}

	FOnMissionClearDelegate MissionClearDeleagate;
};

UCLASS()
class LUNARMODULARBASE_API UMission : public UObject
{
	GENERATED_BODY()

public :
	UMission();
	TPair<FString, TObjectPtr<UMission>> Initialize(const struct FMissionData* MissionData);
	
public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName MissionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EMissionType MissionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString MissionDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName MissionItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString MissionScript;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName NeedToClear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ActCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	uint8 bIsShared : 1;

	void MissionClear();

	bool IsNameStableForNetworking() const override;

	bool ClearCheck(EMissionType MissionType, FName ObjID);

	//Mission Clear Section
protected:
	UPROPERTY()
	TMap<EMissionType, FMissionClearWrapper> MissionClearEvents;

	bool CheckWaitForClear(FName InMissionID);

	bool CheckInteractionCountForClear(FName InObjectID);

};
