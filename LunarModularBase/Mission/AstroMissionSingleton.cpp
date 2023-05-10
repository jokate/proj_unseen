// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/AstroMissionSingleton.h"
#include "Mission/Mission.h"

UAstroMissionSingleton::UAstroMissionSingleton()
{
	FString MissionDataPath = TEXT("/Script/Engine.DataTable'/Game/GameData/AstroMissionDatas.AstroMissionDatas'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MISSION(*MissionDataPath);
	if (DT_MISSION.Succeeded())
	{
		MissionTable = DT_MISSION.Object;
		check(MissionTable->GetRowMap().Num() > 0);
	}

	TMap<FName, uint8*> MissionMap = MissionTable->GetRowMap();
	for (auto MissionData : MissionMap) {
		FMissionData Mission = *reinterpret_cast<FMissionData*>(MissionData.Value);
		Missions.Add(MissionData.Key.ToString(), Mission);
	}

	CollabMissionDistributors.Add(EPlayerType::PLAYER_BACK, FCollabMissionDistributor(FOnCollabMissionChange::CreateUObject(this, &UAstroMissionSingleton::AfterClearCollabBack)));
	CollabMissionDistributors.Add(EPlayerType::PLAYER_FRONT, FCollabMissionDistributor(FOnCollabMissionChange::CreateUObject(this, &UAstroMissionSingleton::AfterClearCollabFront)));

}

UAstroMissionSingleton& UAstroMissionSingleton::Get()
{
	// TODO: insert return statement here
	UAstroMissionSingleton* Singleton = CastChecked<UAstroMissionSingleton>(GEngine->GameSingleton);
	if (Singleton) {
		return *Singleton;
	}

	return *NewObject<UAstroMissionSingleton>();
}

UMission* UAstroMissionSingleton::GetMission(uint8 IsCurrentCollab, EPlayerType PlayerType, FString MissionID)
{
	if (IsCurrentCollab == 0) {
		if (auto MissionData = Missions.Find(MissionID)) {
			UMission* RetMission = NewObject<UMission>();
			RetMission->Initialize(Missions.Find(MissionData->NextMissionID.ToString()));
			return RetMission;
		}
		return NewObject<UMission>();
	}
	else {
		return CollabMissionDistributors[PlayerType].CollabMissionDistributor.Execute(MissionID);
	}}

UMission* UAstroMissionSingleton::AfterClearCollabFront(FString InMissionID)
{
	auto MissionData = Missions.Find(InMissionID);
	auto MissionDataFront = Missions.Find(MissionData->AfterSharedFront.ToString());
	if (MissionDataFront) 
	{
		UMission* Mission = NewObject<UMission>();
		Mission->Initialize(MissionDataFront);
		return Mission;

	}
	return nullptr;
}

UMission* UAstroMissionSingleton::AfterClearCollabBack(FString InMissionID)
{
	auto MissionData = Missions.Find(InMissionID);
	auto MissionDataBack = Missions.Find(MissionData->AfterSharedBack.ToString());
	if (MissionDataBack)
	{
		UMission* Mission = NewObject<UMission>();
		Mission->Initialize(MissionDataBack);
		return Mission;

	}
	return nullptr;
}

FString UAstroMissionSingleton::ReturnMissionScript(FName InMissionID)
{
	auto MissionData = Missions.Find(InMissionID.ToString());
	FString ReturnString;
	check(MissionData);
	if (!MissionData->MissionScript.IsEmpty() || !MissionData->MissionScript.Equals(TEXT("")))
		return MissionData->MissionScript;
	return ReturnString;
}

FString UAstroMissionSingleton::ReturnMissionDescription(FName InMissionID)
{
	auto MissionData = Missions.Find(InMissionID.ToString());
	check(MissionData);
	return MissionData->MissionDesc;
}

