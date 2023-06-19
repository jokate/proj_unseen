// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroTriggerInteractiveObjectPW.h"
#include "Components/WidgetComponent.h"
#include "UI/AstroInteractionObj/AstroInteractPassword.h"
#include "InteractiveObject/InteractionObjDataAsset.h"
#include "Interface/InteractionWidgetInterface.h"
AAstroTriggerInteractiveObjectPW::AAstroTriggerInteractiveObjectPW() 
{
	static ConstructorHelpers::FClassFinder<UAstroInteractPassword> ASTRO_PASSWORD_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_Password.ASTRO_Password_C'"));
	if(ASTRO_PASSWORD_WIDGET.Class) 
	{
		PasswordClass = ASTRO_PASSWORD_WIDGET.Class;
	}
}




void AAstroTriggerInteractiveObjectPW::SetObjActiveComplete()
{
	AAstroInteractableObject::SetObjActiveComplete();

}

void AAstroTriggerInteractiveObjectPW::BeginPlay()
{
	Super::BeginPlay();	
}

void AAstroTriggerInteractiveObjectPW::SetPercentage(float Infloat)
{
	ActivationPercent = Infloat;
	IInteractionWidgetInterface* Widget = Cast<IInteractionWidgetInterface>(ActivationWidget->GetWidget());
	if (Widget) {
		Widget->SetPercentage(ActivationPercent);
		if (ActivationPercent > ActivationFullPercent)
		{
			SetObjActiveComplete();	
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

			if (PlayerController)
			{
				UE_LOG(LogTemp, Warning, TEXT("PASSWORD SET"));
				PasswordWidget = CastChecked<UAstroInteractPassword>(CreateWidget(PlayerController, PasswordClass));
				PasswordWidget->AddToViewport();
				PasswordWidget->SetOwner(this);
				SetPercentage(0.0f);
			}
			GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
		}
	}
}

bool AAstroTriggerInteractiveObjectPW::ComparePassword(const FString& InPassword)
{
	return PasswordString.Equals(InPassword);
}

