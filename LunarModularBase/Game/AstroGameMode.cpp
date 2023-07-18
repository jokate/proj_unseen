// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroGameMode.h"
#include "Game/AstroPlayerState.h"
#include "Game/AstroGameState.h"
#include "Game/AstroClassDataSet.h"

#include "GameFramework/HUD.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/AssetManager.h"
#include "Player/AstroController.h"

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

	bUseSeamlessTravel = true;
}

void AAstroGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AAstroGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AAstroGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
	auto NewAstroController = CastChecked<AAstroController>(NewPC);
	auto OldAstroController = CastChecked<AAstroController>(OldPC);
	NewAstroController->CurrentPlayerType = OldAstroController->CurrentPlayerType;
}


#pragma region Mission Clear Check Part
void AAstroGameMode::InMissionIDEventOccured(FName InID)
{
	MissionManager->InMissionIDEventOccured(InID);
}


#pragma endregion