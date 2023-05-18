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
	//FOnMissionObjectActive Event = UAstroMissionSingleton::Get().GetMissionObjectDelegate();
	//if (!Event.IsBoundToObject(this)) {
	//	Event.AddUObject(this, &AAstroFrontCharacter::Req_MissionClear);
	//	UE_LOG(LogTemp, Log, TEXT("Not Bound Bound Completed"));
	//}
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

void AAstroFrontCharacter::OnMissionObjectCollided(FOnActivatedComplete& InActivatedDelegate)
{
	InActivatedDelegate.BindUObject(this, &AAstroFrontCharacter::Req_MissionClear);
}

void AAstroFrontCharacter::OnItemObjectCollided(FOnTakeItemDelegate& InTakeItemDelegate)
{
	InTakeItemDelegate.BindUObject(this, &AAstroFrontCharacter::TakeItem);
}





