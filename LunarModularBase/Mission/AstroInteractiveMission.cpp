// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/AstroInteractiveMission.h"

UAstroInteractiveMission::UAstroInteractiveMission()
{
	MissionType = EMissionType::MISSION_INTERACTION;
	ClearChecker.Add(EInteractiveType::NORMAL, FInteractiveMissionChecker(FOnInteractiveMissionClear::CreateUObject(this, &UAstroInteractiveMission::InteractiveMissionClearNormal)));
	ClearChecker.Add(EInteractiveType::TIMELIMIT, FInteractiveMissionChecker(FOnInteractiveMissionClear::CreateUObject(this, &UAstroInteractiveMission::InteractiveMissionClearInTime)));
	ClearChecker.Add(EInteractiveType::SEQUENTIAL, FInteractiveMissionChecker(FOnInteractiveMissionClear::CreateUObject(this, &UAstroInteractiveMission::InteractiveMissionClearSequential)));
}

bool UAstroInteractiveMission::ClearCheck(FName ObjID)
{
	if (ClearChecker.Find(InteractionType))
	{
		return ClearChecker[InteractionType].MissionClear.Execute(ObjID);
	}
	return false;
}

void UAstroInteractiveMission::OnTimerUnCleared()
{
	if (ActCount > 0) {
		ActCount = OriginalActCount;
	}
}


bool UAstroInteractiveMission::InteractiveMissionClearInTime(FName InObjID)
{
	if (!MissionItemIDs.Contains(InObjID))
		return false;

	if (!InteractiveMissionClearNormal(InObjID)) {
		OwningActor->GetWorld()->GetTimerManager().SetTimer(ActivationTimer, this, &UAstroInteractiveMission::OnTimerUnCleared, ActiveTime, false);
		return false;
	}
	else {
		ActivationTimer.Invalidate();
		return true;
	}
}

bool UAstroInteractiveMission::InteractiveMissionClearNormal(FName InObjID)
{
	if (MissionItemIDs.Contains(InObjID)) {
		--ActCount;
		if (ActCount == 0) {
			return true;
		}
	}
	return false;
}

bool UAstroInteractiveMission::InteractiveMissionClearSequential(FName InObjID)
{
	if(MissionItemIDs[SequentialIndex].IsEqual(InObjID)) 
	{
		SequentialIndex = FMath::Clamp(SequentialIndex + 1, 0, MissionItemIDs.Num());
		UE_LOG(LogTemp, Warning, TEXT("%s : Index : %d"), *GetName(), SequentialIndex)
		if (SequentialIndex == MissionItemIDs.Num())
			return true;
	}
	else if(MissionItemIDs.Contains(InObjID))
	{
		SequentialIndex = 0;
	}
	return false;
}

void UAstroInteractiveMission::Initialize(FName InMissionID, const FMissionData MissionData, const FInteractiveMissionData InteractiveMissionData)
{
	Initialize(InMissionID, MissionData);
	ActCount = InteractiveMissionData.ActCount;
	OriginalActCount = ActCount;
	InteractionType = InteractiveMissionData.InteractionType;
	MissionItemIDs = InteractiveMissionData.MissionItemIDs;
	ActiveTime = InteractiveMissionData.Time;
}

void UAstroInteractiveMission::Initialize(FName InMissionID, const FMissionData MissionData)
{
	Super::Initialize(InMissionID, MissionData);
}
