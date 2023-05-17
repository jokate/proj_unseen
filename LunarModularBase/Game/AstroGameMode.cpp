// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroGameMode.h"
#include "Game/AstroPlayerState.h"
#include "Game/AstroGameState.h"
#include "Game/AstroClassDataSet.h"

#include "GameFramework/HUD.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/AssetManager.h"

#include "Mission/Missions.h"
#include "Mission/AstroMissionSingleton.h"


AAstroGameMode::AAstroGameMode()
{
	static ConstructorHelpers::FObjectFinder<UAstroClassDataSet> CLASS_DATAS(TEXT("/Script/LunarModularBase.AstroClassDataSet'/Game/DataAsset/ASTRO_PlayerClass.ASTRO_PlayerClass'"));
	if (CLASS_DATAS.Object) {
		ClassDataAsset = CLASS_DATAS.Object;
	}

	static ConstructorHelpers::FClassFinder<APawn> PAWN_CLASS(TEXT("'/Script/LunarModularBase.AstroCharacter'"));
	if (PAWN_CLASS.Succeeded()) {
		DefaultPawnClass = PAWN_CLASS.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APlayerController> CONTROLLER_CLASS(TEXT("'/Script/LunarModularBase.AstroController'"));
	if (CONTROLLER_CLASS.Succeeded()) {
		PlayerControllerClass = CONTROLLER_CLASS.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> HUD_CLASS(TEXT("'/Script/LunarModularBase.AstroHUD'"));
	if (HUD_CLASS.Succeeded()) {
		HUDClass = HUD_CLASS.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerState> STATE_CLASS(TEXT("'/Script/LunarModularBase.AstroPlayerState'"));
	if (STATE_CLASS.Succeeded()) {
		PlayerStateClass = STATE_CLASS.Class;
	}
	static ConstructorHelpers::FClassFinder<AGameStateBase> GAME_STATE_CLASS(TEXT("'/Script/LunarModularBase.AstroGameState'"));
	if (GAME_STATE_CLASS.Class) {
		GameStateClass = GAME_STATE_CLASS.Class;
	}

	MissionClearChecker.AddUObject(this, &AAstroGameMode::FrontwardMissionClearChecker);
	MissionClearChecker.AddUObject(this, &AAstroGameMode::BackwardMissionClearChecker);

	MissionClearCheckEvent.Add(EMissionType::MISSION_INTERACTION, FMissionChecker(FOnMissionClearCheck::CreateUObject(this, &AAstroGameMode::InteractiveMissionClearCheck)));
	MissionClearCheckEvent.Add(EMissionType::MISSION_WAIT, FMissionChecker(FOnMissionClearCheck::CreateUObject(this, &AAstroGameMode::WaitMissionClearCheck)));


}

void AAstroGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AAstroGameMode::BeginPlay()
{
	Super::BeginPlay();

	//For Test
	BackwardMission = UAstroMissionSingleton::Get().GetMission("B_01");
	BackwardMission->SetOwningActor(this);
	FrontwardMission = UAstroMissionSingleton::Get().GetMission("F_01");
	FrontwardMission->SetOwningActor(this);
	AAstroGameState* AstroGameState = CastChecked<AAstroGameState>(GetWorld()->GetGameState());
	if (AstroGameState)
	{
		AstroGameState->SetFrontMissionID(FrontwardMission->MissionID);
		AstroGameState->SetBackMissionID(BackwardMission->MissionID);
	}
}


APlayerController* AAstroGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	if (NumberOfPlayer % PlayerSide == 0) {
		DefaultPawnClass = ClassDataAsset->AstroCharacterClasses[0];
	}
	else {
		DefaultPawnClass = ClassDataAsset->AstroCharacterClasses[1];
	}
	++NumberOfPlayer;

	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AAstroGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}


#pragma region Mission Clear Check Part
void AAstroGameMode::InMissionIDEventOccured(FName InID)
{
	MissionClearChecker.Broadcast(InID);
}


#pragma endregion

void AAstroGameMode::FrontwardMissionClearChecker(FName InID)
{
	check(FrontwardMission)
	if (MissionClearCheckEvent[FrontwardMission->MissionType].MissionClearCheck.Execute(FrontwardMission, InID))
	{
		FName PrevMissionID = FrontwardMission->MissionID;
		FrontwardMissionSetter();
		MissionClearedEvent(PrevMissionID);
	}
}

void AAstroGameMode::FrontwardMissionSetter()
{
	UAstroMissionBase* Mission = UAstroMissionSingleton::Get().GetMission(FrontwardMission->NextMissionID);
	Mission->SetOwningActor(this);
	FrontwardMission = Mission;
	FrontwardGameStateSetter();
}

void AAstroGameMode::FrontwardGameStateSetter()
{
	AAstroGameState* AstroGameState = CastChecked<AAstroGameState>(GetWorld()->GetGameState());
	if (AstroGameState)
	{
		AstroGameState->SetFrontMissionID(FrontwardMission->MissionID);
	}
}

void AAstroGameMode::BackwardMissionClearChecker(FName InID)
{
	check(BackwardMission)
	if (MissionClearCheckEvent[BackwardMission->MissionType].MissionClearCheck.Execute(BackwardMission, InID))
	{
		FName PrevMissionID = BackwardMission->MissionID;
		BackwardMissionSetter();
		MissionClearedEvent(PrevMissionID);
	}
}

void AAstroGameMode::BackwardMissionSetter()
{
	UAstroMissionBase* Mission = UAstroMissionSingleton::Get().GetMission(BackwardMission->NextMissionID);
	Mission->SetOwningActor(this);
	BackwardMission = Mission;

	BackwardGameStateSetter();
}

void AAstroGameMode::BackwardGameStateSetter()
{
	AAstroGameState* AstroGameState = CastChecked<AAstroGameState>(GetWorld()->GetGameState());
	if (AstroGameState)
	{
		AstroGameState->SetBackMissionID(BackwardMission->MissionID);
	}
}

void AAstroGameMode::MissionClearedEvent(FName InID)
{
	if (!MissionClearedList.Contains(InID)) {
		MissionClearedList.Emplace(InID);
		InMissionIDEventOccured(InID);
	}
}

bool AAstroGameMode::InteractiveMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID)
{
	UAstroInteractiveMission* InteractiveMission = CastChecked<UAstroInteractiveMission>(MissionBase);
	if (InteractiveMission) {
		return InteractiveMission->ClearCheck(InObjID);
	}
	return false;
}


bool AAstroGameMode::WaitMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID)
{
	UAstroWaitMission* WaitMission = Cast<UAstroWaitMission>(MissionBase);
	if (WaitMission) {
		return WaitMission->ClearCheck(InObjID);
	}
	return false;
}
