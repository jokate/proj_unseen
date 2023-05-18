// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroGameMode.h"
#include "Game/AstroPlayerState.h"
#include "Game/AstroGameState.h"
#include "Game/AstroClassDataSet.h"

#include "GameFramework/HUD.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/AssetManager.h"

#include "Mission/MissionManagementComponent.h"


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
	
	MissionManager = CreateDefaultSubobject<UMissionManagementComponent>("MISSIONMANAGER");

}

void AAstroGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AAstroGameMode::BeginPlay()
{
	Super::BeginPlay();
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
	MissionManager->InMissionIDEventOccured(InID);
}


#pragma endregion