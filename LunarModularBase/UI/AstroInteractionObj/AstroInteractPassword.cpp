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

void UAstroInteractPassword::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (GetVisibility() == ESlateVisibility::Visible)
		OnVisible();
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
		OnInvisible();
		IAstroCharacterInterface* AstroCharacter = CastChecked<IAstroCharacterInterface>(GetOwningPlayerPawn());
		IAstroPwInteractInterface* PwObject = CastChecked<IAstroPwInteractInterface>(Owner);
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
	OnInvisible();
	IInteractableObjectInterface* PasswordOwner = CastChecked<IInteractableObjectInterface>(Owner);
	PasswordOwner->SetTriggerEnable();
}

void UAstroInteractPassword::OnInvisible()
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
