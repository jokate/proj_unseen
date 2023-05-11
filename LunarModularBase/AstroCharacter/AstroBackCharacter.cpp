// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacter/AstroBackCharacter.h"
#include "Mission/AstroMissionSingleton.h"
#include "Mission/MissionComponent.h"
#include "Item/AstroItemData.h"
AAstroBackCharacter::AAstroBackCharacter()
{
	Tags.Add("BACK");
}

void AAstroBackCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AAstroBackCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerTypeSetting(EPlayerType::PLAYER_BACK);
}

void AAstroBackCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAstroBackCharacter::Req_MissionClear(FName ObjectName)
{
	FString RequestID = ObjectName.ToString();
	if (!RequestID.Contains(ASTRO_COOP_ID))
		RequestID = ASTRO_BACK_ID + RequestID;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *RequestID);
	MissionComponent->ClearCheck(FName(*RequestID));
}

void AAstroBackCharacter::TakeItem(UAstroItemData* InItemData)
{
	Super::TakeItem(InItemData);
	Req_MissionClear(InItemData->ItemID);
}

