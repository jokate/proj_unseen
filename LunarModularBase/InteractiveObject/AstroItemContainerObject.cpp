// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/AstroItemContainerObject.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Interface/InteractionWidgetInterface.h"

void AAstroItemContainerObject::PostInitializeComponents()
{
	AActor::PostInitializeComponents();
	ObjectTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAstroItemContainerObject::OnCharacterOverlap);
	ObjectTrigger->OnComponentEndOverlap.AddDynamic(this, &AAstroItemContainerObject::OnCharacterOverlapOut);
}

void AAstroItemContainerObject::BeginPlay()
{
	AActor::BeginPlay();
}

void AAstroItemContainerObject::SetObjActiveComplete()
{
	OnItemIsGiven.ExecuteIfBound(ObjectItemData);

	Super::SetObjActiveComplete();
}

void AAstroItemContainerObject::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	auto ItemInterfaceCast = Cast<IAstroItemInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && ItemInterfaceCast)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Init"));
		ItemInterfaceCast->OnItemObjectCollided(OnItemIsGiven);
	}
}

void AAstroItemContainerObject::OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCharacterOverlapOut(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	auto ItemInterfaceCast = Cast<IAstroItemInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && ItemInterfaceCast)
	{
		OnItemIsGiven.Unbind();
	}
}
