// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroGameState.h"
#include "Game/AstroPlayerState.h"
#include "Interface/AstroMissionClearInterface.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/PlayerController.h"

AAstroGameState::AAstroGameState()
{
	CurrentFrontMissionID = "";
	CurrentBackMissionID = "";
	bReplicates = true;
}

void AAstroGameState::SetFrontMissionID(FName InMissionID)
{
	AddClearedMissionToList(CurrentFrontMissionID);
	CurrentFrontMissionID = InMissionID;

	if (HasAuthority()) {
		IAstroMissionClearInterface* Pawn = Cast<IAstroMissionClearInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Pawn) {
			if (Pawn->ReturnTag() == EPlayerType::PLAYER_FRONT) {
				UE_LOG(LogTemp, Log, TEXT("SERVER_FRONTMISSIONUPDATED"));
				Pawn->HUDUpdate(CurrentFrontMissionID);
			}
		}
	}
}

void AAstroGameState::SetBackMissionID(FName InMissionID)
{
	AddClearedMissionToList(CurrentBackMissionID);
	CurrentBackMissionID = InMissionID;

	if (HasAuthority()) {
		IAstroMissionClearInterface* Pawn = Cast<IAstroMissionClearInterface>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Pawn) {
			if (Pawn->ReturnTag() == EPlayerType::PLAYER_BACK) {
				UE_LOG(LogTemp, Log, TEXT("SERVER_BACKMISSIONUPDATED"));
				Pawn->HUDUpdate(CurrentBackMissionID);
			}
		}
	}
}

void AAstroGameState::BeginPlay()
{
	Super::BeginPlay();

}

void AAstroGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAstroGameState, CurrentFrontMissionID);
	DOREPLIFETIME(AAstroGameState, CurrentBackMissionID);
	DOREPLIFETIME(AAstroGameState, ClearedMissionList);
}

void AAstroGameState::FrontMissionIDUpdated()
{
	IAstroMissionClearInterface* Pawn = Cast<IAstroMissionClearInterface>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn());
	if (Pawn) {
		if (Pawn->ReturnTag() == EPlayerType::PLAYER_FRONT) {
			UE_LOG(LogTemp, Log, TEXT("FRONTMISSIONUPDATED"));
			Pawn->HUDUpdate(CurrentFrontMissionID);
		}
	}
}

void AAstroGameState::BackMissionIDUpdated()
{
	IAstroMissionClearInterface* Pawn = Cast<IAstroMissionClearInterface>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn());
	if (Pawn) {
		if (Pawn->ReturnTag() == EPlayerType::PLAYER_BACK) {
			UE_LOG(LogTemp, Log, TEXT("BACKMISSIONUPDATED"));
			Pawn->HUDUpdate(CurrentBackMissionID);
		}
	}
}

void AAstroGameState::AddClearedMissionToList(FName InMissionName)
{
	if(!ClearedMissionList.Contains(InMissionName) || !InMissionName.IsEqual("None"))
		ClearedMissionList.Add(InMissionName);
}

bool AAstroGameState::IsContainMissionID(FName InMissionID)
{
	return ClearedMissionList.Contains(InMissionID);
}

FName AAstroGameState::GetInitiailizedMissionID(EPlayerType PlayerType)
{
	if (PlayerType == EPlayerType::PLAYER_FRONT)
		return CurrentFrontMissionID;
	else
		return CurrentBackMissionID;
}
