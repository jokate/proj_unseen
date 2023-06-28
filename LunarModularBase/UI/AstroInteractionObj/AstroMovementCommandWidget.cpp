// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AstroInteractionObj/AstroMovementCommandWidget.h"
#include "Interface/AstroCharacterInterface.h"


void UAstroMovementCommandWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UAstroMovementCommandWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (GetVisibility() == ESlateVisibility::Visible)
		OnVisible();
}

void UAstroMovementCommandWidget::SetOwner(UActorComponent* InOwner)
{	
	SetVisibility(ESlateVisibility::Visible);
	Owner = InOwner;
}

void UAstroMovementCommandWidget::MoveObject(EDirection Direction)
{
	auto Character = CastChecked<IAstroCharacterInterface>(GetOwningPlayerPawn());
	Character->MoveObject(Owner, Direction);
}

void UAstroMovementCommandWidget::OnVisible()
{
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->DisableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = true;
}

void UAstroMovementCommandWidget::OnInvisible()
{
	SetVisibility(ESlateVisibility::Hidden);
	AActor* CurrentActor = CastChecked<AActor>(GetOwningPlayerPawn());
	CurrentActor->EnableInput(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = false;
}
