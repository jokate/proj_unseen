// Fill out your copyright notice in the Description page of Project Settings.


#include "Mission/MissionComponent.h"
#include "Mission/AstroMissionSingleton.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"

#include "Interface/AstroHUDInterface.h"
#include "Interface/AstroMissionManager.h"
#include "Interface/AstroGameStateInterface.h"
#include "Interface/AstroMissionClearInterface.h"


// Sets default values for this component's properties
UMissionComponent::UMissionComponent()
{
	PlayerType = EPlayerType::PLAYER_NONE;

}

void UMissionComponent::Init()
{
	auto AstroGameState = CastChecked<IAstroGameStateInterface>(GetWorld()->GetGameState());
	auto OwningCharacter = CastChecked<IAstroMissionClearInterface>(GetOwner());
	if (OwningCharacter->GetLocalPlayerTag() == OwningCharacter->ReturnTag() && GetOwner()->GetLocalRole() == ENetRole::ROLE_Authority) {
		FName InitializedMission = AstroGameState->GetInitiailizedMissionID(OwningCharacter->ReturnTag());
		if (!InitializedMission.IsNone())
			MissionHUDUpdate(InitializedMission);
	}
}

void UMissionComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->OnWorldBeginPlay.AddUObject(this, &UMissionComponent::Init);
}

void UMissionComponent::ClearCheck_Implementation(FName ObjectName)
{
	auto MissionManager = CastChecked<IAstroMissionManager>(GetWorld()->GetAuthGameMode());
	MissionManager->InMissionIDEventOccured(ObjectName);
}

void UMissionComponent::MissionHUDUpdate(FName InMissionID)
{
	MissionDescriptionUpdate(InMissionID);
	MissionClearScriptUpdate(InMissionID);
}

void UMissionComponent::MissionDescriptionUpdate(FName InMissionID)
{
	auto SampleHUD = Cast<IAstroHUDInterface>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetHUD());
	if (SampleHUD != nullptr) {
		FString InString = FString::Printf(TEXT("%s"), *UAstroMissionSingleton::Get().ReturnMissionDescription(InMissionID));
		SampleHUD->UpdateMissionText(InString);

	}
}

void UMissionComponent::MissionClearScriptUpdate(FName InMissionID)
{

	auto SampleHUD = Cast<IAstroHUDInterface>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetHUD());
	if (SampleHUD != nullptr) {
		TArray<FString> CompleteString = UAstroMissionSingleton::Get().ReturnMissionScript(InMissionID);
		SampleHUD->UpdateMissionDialogText(CompleteString);
	}

}



