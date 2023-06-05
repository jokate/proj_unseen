// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/MissionManagementComponent.h"

#include "GameFramework/GameStateBase.h"
#include "Engine/AssetManager.h"
#include "Interface/AstroGameStateInterface.h"
#include "Mission/Missions.h"
#include "Mission/AstroMissionSingleton.h"

// Sets default values for this component's properties
UMissionManagementComponent::UMissionManagementComponent()
{
	bWantsInitializeComponent = true;
	MissionClearChecker.AddUObject(this, &UMissionManagementComponent::FrontwardMissionClearChecker);
	MissionClearChecker.AddUObject(this, &UMissionManagementComponent::BackwardMissionClearChecker);

	MissionClearCheckEvent.Add(EMissionType::MISSION_INTERACTION, FMissionChecker(FOnMissionClearCheck::CreateUObject(this, &UMissionManagementComponent::InteractiveMissionClearCheck)));
	MissionClearCheckEvent.Add(EMissionType::MISSION_WAIT, FMissionChecker(FOnMissionClearCheck::CreateUObject(this, &UMissionManagementComponent::WaitMissionClearCheck)));
}

void UMissionManagementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UMissionManagementComponent::BeginPlay()
{
	Super::BeginPlay();
	//For Test
	BackwardMission = UAstroMissionSingleton::Get().GetMission("B_01");
	BackwardMission->SetOwningActor(GetOwner());
	FrontwardMission = UAstroMissionSingleton::Get().GetMission("F_01");
	FrontwardMission->SetOwningActor(GetOwner());
	IAstroGameStateInterface* AstroGameState = CastChecked<IAstroGameStateInterface>(GetWorld()->GetGameState());
	if (AstroGameState)
	{
		AstroGameState->SetFrontMissionID(FrontwardMission->MissionID);
		AstroGameState->SetBackMissionID(BackwardMission->MissionID);
	}
}


void UMissionManagementComponent::InMissionIDEventOccured(FName InID)
{
	MissionClearChecker.Broadcast(InID);
}


#pragma endregion

void UMissionManagementComponent::FrontwardMissionClearChecker(FName InID)
{
	UE_LOG(LogTemp, Warning, TEXT("Front In ID : %s"), *InID.ToString())
	check(FrontwardMission)
	if (MissionClearCheckEvent[FrontwardMission->MissionType].MissionClearCheck.Execute(FrontwardMission, InID))
	{
		FName PrevMissionID = FrontwardMission->MissionID;
		FrontwardMissionSetter();
		MissionClearedEvent(PrevMissionID);
	}
}

void UMissionManagementComponent::FrontwardMissionSetter()
{
	UAstroMissionBase* Mission = UAstroMissionSingleton::Get().GetMission(FrontwardMission->NextMissionID);
	Mission->SetOwningActor(GetOwner());
	FrontwardMission = Mission;
	FrontwardGameStateSetter();
}

void UMissionManagementComponent::FrontwardGameStateSetter()
{
	IAstroGameStateInterface* AstroGameState = CastChecked<IAstroGameStateInterface>(GetOwner()->GetWorld()->GetGameState());
	if (AstroGameState)
	{
		AstroGameState->SetFrontMissionID(FrontwardMission->MissionID);
	}
}

void UMissionManagementComponent::BackwardMissionClearChecker(FName InID)
{
	UE_LOG(LogTemp, Warning, TEXT("Back In ID : %s"), *InID.ToString())
	check(BackwardMission)
		if (MissionClearCheckEvent[BackwardMission->MissionType].MissionClearCheck.Execute(BackwardMission, InID))
		{
			FName PrevMissionID = BackwardMission->MissionID;
			BackwardMissionSetter();
			MissionClearedEvent(PrevMissionID);
		}
}

void UMissionManagementComponent::BackwardMissionSetter()
{
	UAstroMissionBase* Mission = UAstroMissionSingleton::Get().GetMission(BackwardMission->NextMissionID);
	Mission->SetOwningActor(GetOwner());
	BackwardMission = Mission;

	BackwardGameStateSetter();
}

void UMissionManagementComponent::BackwardGameStateSetter()
{
	IAstroGameStateInterface* AstroGameState = CastChecked<IAstroGameStateInterface>(GetWorld()->GetGameState());
	if (AstroGameState)
	{
		AstroGameState->SetBackMissionID(BackwardMission->MissionID);
	}
}

void UMissionManagementComponent::MissionClearedEvent(FName InID)
{
	if (!MissionClearedList.Contains(InID)) {
		MissionClearedList.Emplace(InID);
		InMissionIDEventOccured(InID);
	}
}

bool UMissionManagementComponent::InteractiveMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID)
{
	UAstroInteractiveMission* InteractiveMission = CastChecked<UAstroInteractiveMission>(MissionBase);
	if (InteractiveMission) {
		return InteractiveMission->ClearCheck(InObjID);
	}
	return false;
}


bool UMissionManagementComponent::WaitMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID)
{
	UAstroWaitMission* WaitMission = Cast<UAstroWaitMission>(MissionBase);
	if (WaitMission) {
		return WaitMission->ClearCheck(InObjID);
	}
	return false;
}
