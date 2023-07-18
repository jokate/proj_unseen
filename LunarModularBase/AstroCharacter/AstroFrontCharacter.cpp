// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacter/AstroFrontCharacter.h"
#include "Mission/AstroMissionSingleton.h"
#include "Mission/MissionComponent.h"
#include "Item/AstroItemData.h"

AAstroFrontCharacter::AAstroFrontCharacter()
{
	Tags.Add("FRONT");
}

void AAstroFrontCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerTypeSetting(EPlayerType::PLAYER_FRONT);
}

void AAstroFrontCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAstroFrontCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAstroFrontCharacter::Req_MissionClear(FName ObjectName)
{
	FString RequestID = ObjectName.ToString();
	if (!RequestID.Contains(ASTRO_COOP_ID))
		RequestID = ASTRO_FRONT_ID + RequestID;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *RequestID);
	MissionComponent->ClearCheck(FName(*RequestID));
}

void AAstroFrontCharacter::TakeItem(UAstroItemData* InItemData)
{
	if (!InItemData)
		return;
	Super::TakeItem(InItemData);
	Req_MissionClear(InItemData->ItemID);
}




