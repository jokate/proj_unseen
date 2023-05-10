// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AstroController.h"
#include "Game/AstroPlayerState.h"
#include "Interface/AstroCharacterInterface.h"


AAstroController::AAstroController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void AAstroController::BeginPlay()
{
	Super::BeginPlay();
}

void AAstroController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAstroController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AAstroController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAstroController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAstroController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

}

void AAstroController::OnPossess(APawn* aPawn)
{	
	Super::OnPossess(aPawn);
	//AAstroPlayerState* AstroPlayerState = CastChecked<AAstroPlayerState>(PlayerState);

	//IAstroCharacterInterface* AstroCharacter = Cast<IAstroCharacterInterface>(aPawn);
	//	if (AstroCharacter) {
	//	UE_LOG(LogTemp, Log, TEXT("SET OK"));
	//	AstroCharacter->PlayerTypeSetting(AstroPlayerState->GetPlayerType());
	//}
}



