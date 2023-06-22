// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroTriggerInteractiveObjectPW.h"
#include "InteractiveObject/Components/InteractivePasswordComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Interface/InteractionWidgetInterface.h"
AAstroTriggerInteractiveObjectPW::AAstroTriggerInteractiveObjectPW() 
{
	PasswordComponent = CreateDefaultSubobject<UInteractivePasswordComponent>("PASSWORD");
}

void AAstroTriggerInteractiveObjectPW::BeginPlay()
{
	Super::BeginPlay();	
}


bool AAstroTriggerInteractiveObjectPW::ComparePassword(const FString& InPassword)
{
	if (PasswordComponent->PasswordString.Equals(InPassword))
	{
		K2_OnPasswordEnteredCompletely();
	}
	return PasswordComponent->PasswordString.Equals(InPassword);
}

void  AAstroTriggerInteractiveObjectPW::SetPercentage(float Infloat)
{
	ActivationPercent = Infloat;
	IInteractionWidgetInterface* Widget = Cast<IInteractionWidgetInterface>(ActivationWidget->GetWidget());
	if (Widget) {
		Widget->SetPercentage(ActivationPercent);
		if (ActivationPercent > ActivationFullPercent)
		{
			ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PasswordComponent->PasswordWidgetOnBoard();
			GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
			SetPercentage(0.0f);
		}
	}
}