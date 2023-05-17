// Fill out your copyright notice in the Description page of Project Settings.


#include "AstralBox/AstralTimerBox.h"

void AAstralTimerBox::SetObjActiveComplete() {
	Super::SetObjActiveComplete();
	FTimerHandle ReActivateHandler;

	GetWorld()->GetTimerManager().SetTimer(ReActivateHandler, [&]() {
		SetActorEnableCollision(true);
	}, ReactivateTime, false);
}