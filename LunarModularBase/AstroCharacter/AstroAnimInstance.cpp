// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroAnimInstance.h"
#include "AstroCharacter.h"
#include "AstroCharacterStatusComponent.h"

UAstroAnimInstance::UAstroAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
}

void UAstroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn)) {
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<AAstroCharacter>(Pawn);
		if (Character) {
			IsInAir = Character->GetMovementComponent()->IsFalling();
			Speed = Character->GetCharacterMovement()->MaxWalkSpeed;
			IsExploring = Character->CharacterStat->GetExplore();
			JumpVelocity = Character->GetCharacterMovement()->JumpZVelocity;
			LeftRight = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		}
	}
}

