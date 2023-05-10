// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacter/AstroBackCharacter.h"
#include "Mission/AstroMissionSingleton.h"

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

