// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroMovementCommandObject.h"
#include "Interface/InteractionWidgetInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "InteractiveObject/Components/MovementCommandComponent.h"
#include "InteractiveObject/InteractiveObject/AstroTriggerResponseObject.h"

AAstroMovementCommandObject::AAstroMovementCommandObject()
{
	MovementCommandComponent = CreateDefaultSubobject<UMovementCommandComponent>("MOVEMENT");
	bIsCoolDown = false;
}

void AAstroMovementCommandObject::SetPercentage(float Infloat)
{
	ActivationPercent = Infloat;
	IInteractionWidgetInterface* Widget = Cast<IInteractionWidgetInterface>(ActivationWidget->GetWidget());
	if (Widget) {
		Widget->SetPercentage(ActivationPercent);
		if (ActivationPercent > ActivationFullPercent)
		{
			ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			MovementCommandComponent->MovementCommandActivated();
			GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
			SetPercentage(0.0f);
		}
	}
}

void AAstroMovementCommandObject::MoveObject(EDirection Direction)
{
	if(!bIsCoolDown) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Pressed!"))
		K2_OnObjectMove(Direction);
		bIsCoolDown = true;
		GetWorld()->GetTimerManager().SetTimer(MovementHandle, [&]() {
			bIsCoolDown = false; }, CoolTime, false);
	}

}
