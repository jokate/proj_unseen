// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/AstroMissionSingleton.h"
#include "Mission/Missions.h"

UAstroMissionSingleton::UAstroMissionSingleton()
{
	FString MissionDataPath = TEXT("/Script/Engine.DataTable'/Game/GameData/AstroMissionDatas.AstroMissionDatas'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MISSION(*MissionDataPath);
	if (DT_MISSION.Succeeded())
	{
		MissionTable = DT_MISSION.Object;
		check(MissionTable->GetRowMap().Num() > 0);
		TMap<FName, uint8*> MissionMap = MissionTable->GetRowMap();
		for (auto MissionData : MissionMap) {
			FMissionData Mission = *reinterpret_cast<FMissionData*>(MissionData.Value);
			Missions.Add(MissionData.Key, Mission);
		}
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_INTERACTIVEMISSION(TEXT("/Script/Engine.DataTable'/Game/GameData/AstroInteractiveMissionData.AstroInteractiveMissionData'"));
	if (DT_INTERACTIVEMISSION.Object)
	{
		InteractiveMissionDatabase = DT_INTERACTIVEMISSION.Object;
		TMap<FName, uint8*> InteractiveMissionMap = InteractiveMissionDatabase->GetRowMap();
		for (auto MissionData : InteractiveMissionMap) {
			FInteractiveMissionData Mission = *reinterpret_cast<FInteractiveMissionData*>(MissionData.Value);
			InteractiveMissionData.Add(MissionData.Key, Mission);
		}
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WAITMISSION(TEXT("/Script/Engine.DataTable'/Game/GameData/AstroWaitMissionData.AstroWaitMissionData'"));
	if (DT_WAITMISSION.Object)
	{
		WaitMissionDatabase = DT_WAITMISSION.Object;
		TMap<FName, uint8*> WaitMissionMap = WaitMissionDatabase->GetRowMap();
		for (auto MissionData : WaitMissionMap) {
			FWaitMissionData Mission = *reinterpret_cast<FWaitMissionData*>(MissionData.Value);
			WaitMissionData.Add(MissionData.Key, Mission);
		}
	}
	MissionGenerator.Add(EMissionType::MISSION_INTERACTION, FMissionGenerator(FOnMissionChanged::CreateUObject(this, &UAstroMissionSingleton::InteractiveMissionReturn)));
	MissionGenerator.Add(EMissionType::MISSION_WAIT, FMissionGenerator(FOnMissionChanged::CreateUObject(this, &UAstroMissionSingleton::WaitMissionReturn)));
}

UAstroMissionBase* UAstroMissionSingleton::InteractiveMissionReturn(FName InMissionID)
{
	UAstroInteractiveMission* AstroMission = NewObject<UAstroInteractiveMission>();
	if (Missions.Find(InMissionID), InteractiveMissionData.Find(InMissionID)) {
		AstroMission->Initialize(InMissionID, Missions[InMissionID], InteractiveMissionData[InMissionID]);
		return AstroMission;
	}
	return AstroMission;
}


UAstroMissionBase* UAstroMissionSingleton::WaitMissionReturn(FName InMissionID)
{
	UAstroWaitMission* AstroMission = NewObject<UAstroWaitMission>();
	if (Missions.Find(InMissionID), WaitMissionData.Find(InMissionID)) {
		AstroMission->Initialize(InMissionID, Missions[InMissionID], WaitMissionData[InMissionID]);
		return AstroMission;
	}
	return AstroMission;
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

UAstroMissionBase* UAstroMissionSingleton::GetMission(FName MissionID)
{
	FMissionData* MissionData = Missions.Find(MissionID);
	check(MissionData);
	if (MissionGenerator.Find(MissionData->MissionType)) {
		return MissionGenerator[MissionData->MissionType].MissionChange.Execute(MissionID);
	}
	return nullptr;
}

TArray<FString> UAstroMissionSingleton::ReturnMissionScript(FName InMissionID)
{
	auto MissionData = Missions.Find(InMissionID);
	TArray<FString> ReturnString;
	check(MissionData);
	if (!MissionData->MissionScripts.IsEmpty())
		return MissionData->MissionScripts;
	return ReturnString;
}

FString UAstroMissionSingleton::ReturnMissionDescription(FName InMissionID)
{
	auto MissionData = Missions.Find(InMissionID);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *InMissionID.ToString());
	check(MissionData);
	return MissionData->MissionDesc;
}

