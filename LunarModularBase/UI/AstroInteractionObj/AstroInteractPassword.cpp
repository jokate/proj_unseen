// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AstroInteractionObj/AstroInteractPassword.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Interface/InteractableObjectInterface.h"
#include "Interface/AstroPwInteractInterface.h"
#include "Interface/AstroCharacterInterface.h"

void UAstroInteractPassword::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}
void UAstroInteractPassword::PasswordButtonPress(UButton* InButton)
{
	FString ButtonName = InButton->GetName().Reverse();
	FString CurrentText = PasswordText->GetText().ToString();

	CurrentText.AppendChar(ButtonName[0]);

	PasswordText->SetText(FText::FromString(CurrentText));

}

void UAstroInteractPassword::EnterPress()
{
	IAstroPwInteractInterface* PasswordOwner = CastChecked<IAstroPwInteractInterface>(Owner);
	FString CurrentPw = PasswordText->GetText().ToString();
	if(PasswordOwner->ComparePassword(CurrentPw)) 
	{
		ClosingAction();
		IAstroCharacterInterface* AstroCharacter = CastChecked<IAstroCharacterInterface>(GetOwningPlayerPawn());
		IAstroPwInteractInterface* PwObject = CastChecked<IAstroPwInteractInterface>(Owner);
		IInteractableObjectInterface* InteractableObject = CastChecked<IInteractableObjectInterface>(PwObject->ReturnTriggerObject());
		InteractableObject->SetObjActiveComplete();

		AstroCharacter->ActivationComplete(PwObject->ReturnTriggerObject());

	}
	else 
	{
	}

}

void UAstroInteractPassword::CancelButtonPress()
{
	PasswordText->SetText(FText::FromString(TEXT("")));
}

void UAstroInteractPassword::CloseButtonPress()
{
	ClosingAction();

	IInteractableObjectInterface* PasswordOwner = CastChecked<IInteractableObjectInterface>(Owner);
	PasswordOwner->SetTriggerEnable();

}

void UAstroInteractPassword::ClosingAction()
{
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->EnableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = false;
	CancelButtonPress();
	SetVisibility(ESlateVisibility::Hidden);
}

void UAstroInteractPassword::OnVisible()
{
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->DisableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = true;
}
