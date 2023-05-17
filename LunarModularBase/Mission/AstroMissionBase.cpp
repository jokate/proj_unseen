// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/AstroMissionBase.h"

bool UAstroMissionBase::ClearCheck(FName ObjID)
{
	return false;
}

void UAstroMissionBase::Initialize(FName InMissionID, const FMissionData MissionData)
{
	MissionID = InMissionID;
	NextMissionID = MissionData.NextMissionID;
}