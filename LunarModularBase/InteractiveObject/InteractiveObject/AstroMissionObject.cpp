// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroMissionObject.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "AccessControl/AccessControlComponent.h"
#include "Interface/InteractionWidgetInterface.h"


void AAstroMissionObject::PostInitializeComponents()
{
	AActor::PostInitializeComponents();
	ObjectTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAstroMissionObject::OnCharacterOverlap);
	ObjectTrigger->OnComponentEndOverlap.AddDynamic(this, &AAstroMissionObject::OnCharacterOverlapOut);
}

void AAstroMissionObject::BeginPlay()
{
	AActor::BeginPlay();
}

void AAstroMissionObject::SetObjActiveComplete()
{
	OnActiveCompleted.ExecuteIfBound(ObjectID);

	Super::SetObjActiveComplete();
}

void AAstroMissionObject::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	auto MissionClearInterface = Cast<IAstroMissionClearInterface>(OtherActor);

	if ((OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn()) && MissionClearInterface)
	{
		MissionClearInterface->OnMissionObjectCollided(OnActiveCompleted);
	}
}

void AAstroMissionObject::OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	Super::OnCharacterOverlapOut(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	auto MissionClearInterface = Cast<IAstroMissionClearInterface>(OtherActor);

	if ((OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn()) && MissionClearInterface)
	{
		OnActiveCompleted.Unbind();
	}
}
