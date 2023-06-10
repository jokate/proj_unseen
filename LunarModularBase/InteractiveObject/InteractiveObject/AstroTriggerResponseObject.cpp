// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroTriggerResponseObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAstroTriggerResponseObject::AAstroTriggerResponseObject()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
}

// Called when the game starts or when spawned
void AAstroTriggerResponseObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAstroTriggerResponseObject::SetObjActiveComplete()
{
	K2_OnObjectActive();
}

void AAstroTriggerResponseObject::SetObjDeActivateComplete()
{
	K2_OnObjectDeactive();
}
