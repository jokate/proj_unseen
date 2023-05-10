// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroGameMode.h"
#include "Game/AstroPlayerState.h"
#include "Game/AstroGameState.h"
#include "Game/AstroClassDataSet.h"

#include "GameFramework/HUD.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/AssetManager.h"
#include "Interface/AstroCharacterInterface.h"

#include "Mission/Mission.h"
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
	MissionUpdateEvent.AddUObject(this, &AAstroGameMode::IsFrontWaitMissionCleared);
	MissionUpdateEvent.AddUObject(this, &AAstroGameMode::IsBackWaitMissionCleared);
}

void AAstroGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AAstroGameMode::BeginPlay()
{
	Super::BeginPlay();

	//For Test
	BackwardMission = UAstroMissionSingleton::Get().GetMission(1, EPlayerType::PLAYER_BACK, "I_00");
	FrontwardMission = UAstroMissionSingleton::Get().GetMission(1, EPlayerType::PLAYER_FRONT, "I_00");
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

void AAstroGameMode::FrontwardMissionClearChecker(FName InID)
{
	check(FrontwardMission)
	if (FrontwardMission->ClearCheck(FrontwardMission->MissionType, InID))
	{
		FName PrevMissionID = FrontwardMission->MissionID;
		FrontwardMissionSetter();
		MissionClearedEvent(PrevMissionID);
	}
}

void AAstroGameMode::BackwardMissionClearChecker(FName InID)
{
	check(BackwardMission)
	if (BackwardMission->ClearCheck(BackwardMission->MissionType, InID))
	{
		FName PrevMissionID = BackwardMission->MissionID;
		BackwardMissionSetter();
		MissionClearedEvent(PrevMissionID);
	}
}

void AAstroGameMode::FrontwardMissionSetter()
{
	FrontwardMission = UAstroMissionSingleton::Get().GetMission(FrontwardMission->bIsShared, EPlayerType::PLAYER_FRONT, FrontwardMission->MissionID.ToString());
	AAstroGameState* AstroGameState = CastChecked<AAstroGameState>(GetWorld()->GetGameState());
	if(AstroGameState) 
	{
		AstroGameState->SetFrontMissionID(FrontwardMission->MissionID);
	}
}

void AAstroGameMode::BackwardMissionSetter()
{
	BackwardMission = UAstroMissionSingleton::Get().GetMission(BackwardMission->bIsShared, EPlayerType::PLAYER_BACK, BackwardMission->MissionID.ToString());
	AAstroGameState* AstroGameState = CastChecked<AAstroGameState>(GetWorld()->GetGameState());
	if (AstroGameState)
	{
		AstroGameState->SetBackMissionID(BackwardMission->MissionID);
	}
}

void AAstroGameMode::MissionClearedEvent(FName InID)
{
	if (!ClearedMissionList.Contains(InID)) {
		ClearedMissionList.Add(InID);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *InID.ToString());
		MissionUpdateEvent.Broadcast();
	}
}

void AAstroGameMode::IsFrontWaitMissionCleared()
{
	if (FrontwardMission->NeedToClear.IsValid() && ClearedMissionList.Contains(FrontwardMission->NeedToClear)) 
	{
		InMissionIDEventOccured(FrontwardMission->NeedToClear);
	}
}

void AAstroGameMode::IsBackWaitMissionCleared()
{
	if (BackwardMission->NeedToClear.IsValid() && ClearedMissionList.Contains(BackwardMission->NeedToClear))
	{
		InMissionIDEventOccured(BackwardMission->NeedToClear);
	}
}

#pragma endregion