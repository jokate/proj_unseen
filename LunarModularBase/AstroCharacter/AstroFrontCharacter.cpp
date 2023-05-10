// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacter/AstroFrontCharacter.h"
#include "Mission/AstroMissionSingleton.h"

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



