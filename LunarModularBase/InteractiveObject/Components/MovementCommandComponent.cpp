// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Components/MovementCommandComponent.h"
#include "Interface/AstroHUDInterface.h"
// Sets default values for this component's properties
UMovementCommandComponent::UMovementCommandComponent()
{
	bIsCoolDown = false;
}

void UMovementCommandComponent::MovementCommandActivated()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		auto HUD = CastChecked<IAstroHUDInterface>(PlayerController->GetHUD());
		HUD->SetMovementCommandActive(this);
	}
}

void UMovementCommandComponent::MoveObject(EDirection Direction)
{
	if (!bIsCoolDown)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pressed!"))
		MovementStarted.Broadcast(Direction);
		bIsCoolDown = true;
		GetWorld()->GetTimerManager().SetTimer(MovementHandle, [&]() {
			bIsCoolDown = false; }, CoolTime, false);
	}
}




