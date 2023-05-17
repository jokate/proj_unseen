// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/AstroInteractiveMission.h"

UAstroInteractiveMission::UAstroInteractiveMission()
{
	MissionType = EMissionType::MISSION_INTERACTION;
}

bool UAstroInteractiveMission::ClearCheck(FName ObjID)
{
	if (ObjID == MissionItemID) {
		--ActCount;
		if (ActCount == 0) {
			return true;
		}
	}
	return false;
}

void UAstroInteractiveMission::OnTimerUnCleared()
{
	if (ActCount > 0) {
		UE_LOG(LogTemp, Warning, TEXT("TOO LATE"));
		ActCount = OriginalActCount;
	}
}


void UAstroInteractiveMission::Initialize(FName InMissionID, const FMissionData MissionData, const FInteractiveMissionData InteractiveMissionData)
{
	Initialize(InMissionID, MissionData);
	ActCount = InteractiveMissionData.ActCount;
	OriginalActCount = ActCount;
	InteractionType = InteractiveMissionData.InteractionType;
	MissionItemID = InteractiveMissionData.MissionItemID;
	ActiveTime = InteractiveMissionData.Time;
}

void UAstroInteractiveMission::Initialize(FName InMissionID, const FMissionData MissionData)
{
	Super::Initialize(InMissionID, MissionData);
}
