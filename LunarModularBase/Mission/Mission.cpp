// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/Mission.h"
#include "Interface/AstroMissionManager.h"
#include "GameFramework/GameStateBase.h"

UMission::UMission()
{
	MissionClearEvents.Add(EMissionType::MISSION_INTERACTION, FMissionClearWrapper(FOnMissionClearDelegate::CreateUObject(this, &UMission::CheckInteractionCountForClear)));
	MissionClearEvents.Add(EMissionType::MISSION_WAIT, FMissionClearWrapper(FOnMissionClearDelegate::CreateUObject(this, &UMission::CheckWaitForClear)));
}

TPair<FString, TObjectPtr<UMission>> UMission::Initialize(const FMissionData* MissionData)
{
	TPair<FString, TObjectPtr<UMission>> RetMissionPair;
	ActCount = MissionData->ActCount;
	MissionID = MissionData->MissionID;
	MissionType = MissionData->MissionType;
	MissionDesc = MissionData->MissionDesc;
	MissionItemID = MissionData->MissionItemID;
	MissionScript = MissionData->MissionScript;
	NeedToClear = MissionData->NeedToClear;
	bIsShared = MissionData->bIsSharedGoal;
	RetMissionPair.Key = this->MissionID.ToString();
	RetMissionPair.Value = this;
	
	return RetMissionPair;
}

void UMission::MissionClear()
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *MissionScript);
}

bool UMission::IsNameStableForNetworking() const
{
	return true;
}

bool UMission::ClearCheck(EMissionType InMissionType, FName ObjID)
{
	if (FMissionClearWrapper* Mission = MissionClearEvents.Find(InMissionType))
	{
		if (Mission->MissionClearDeleagate.IsBound()) 
		{
			return Mission->MissionClearDeleagate.Execute(ObjID);
		}
	}
	return false;
}

//Return Always True Because it will call when the prerequisite is satisfied
bool UMission::CheckWaitForClear(FName InMissionID)
{
	if (NeedToClear == InMissionID)
		return true;
	else
		return false;
}

bool UMission::CheckInteractionCountForClear(FName InObjectID)
{
	if (InObjectID == MissionItemID) {
		--ActCount;
		if (ActCount == 0) {
			MissionClear();
			return true;
		}
	}
	return false;
}
