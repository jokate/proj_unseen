// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroTriggerMoveResponseObject.h"

AAstroTriggerMoveResponseObject::AAstroTriggerMoveResponseObject()
{
	NeedToRev = false;
}

void AAstroTriggerMoveResponseObject::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AAstroTriggerMoveResponseObject::SetObjActiveComplete()
{	
	if(HasAuthority())
		GetWorld()->GetTimerManager().SetTimer(ActivationHandle, this, &AAstroTriggerMoveResponseObject::MoveObject, MoveRate, true);

	Super::SetObjActiveComplete();
}

void AAstroTriggerMoveResponseObject::SetObjDeActivateComplete()
{
	if(HasAuthority())
		GetWorld()->GetTimerManager().ClearTimer(ActivationHandle);

	Super::SetObjDeActivateComplete();
}


void AAstroTriggerMoveResponseObject::MoveObject()
{
	if(!NeedToRev) 
	{
		LerpingPoint = LerpingPoint + (MoveRate * MoveSpeed);
		if(LerpingPoint >= 1.0f) 
		{
			NeedToRev = true;
		}
		SetActorLocation(FMath::Lerp(InitialPos, TargetPos, LerpingPoint));
		
	}
	else 
	{
		LerpingPoint = LerpingPoint - (MoveRate * MoveSpeed);
		if (LerpingPoint <= 0.0f)
		{
			NeedToRev = false;
		}
		SetActorLocation(FMath::Lerp(InitialPos, TargetPos, LerpingPoint));
	}
}
