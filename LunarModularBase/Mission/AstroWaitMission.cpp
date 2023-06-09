// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/AstroWaitMission.h"
#include "Interface/AstroGameStateInterface.h"

UAstroWaitMission::UAstroWaitMission()
{
	MissionType = EMissionType::MISSION_WAIT;
}

bool UAstroWaitMission::ClearCheck(FName ObjID)
{

	IAstroGameStateInterface* AstroGameState = CastChecked<IAstroGameStateInterface>(OwningActor->GetWorld()->GetGameState());
	return AstroGameState->IsContainMissionID(NeedToClear);
}

void UAstroWaitMission::Initialize(FName InMissionID, const FMissionData MissionData, const FWaitMissionData WaitMissionData)
{
	Initialize(InMissionID, MissionData);
	NeedToClear = WaitMissionData.NeedToClear;
}

void UAstroWaitMission::Initialize(FName InMissionID, const FMissionData MissionData)
{
	Super::Initialize(InMissionID, MissionData);
}

