// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/Trigger/AstroInteractionTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveObject/InteractiveObject/AstroTriggerResponseObject.h"

// Sets default values
AAstroInteractionTrigger::AAstroInteractionTrigger()
{
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATIC MESH"));
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));	

	RootComponent = ObjectMesh;
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->SetCollisionProfileName(TEXT("ObjectTrigger"));
}

// Called when the game starts or when spawned
void AAstroInteractionTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AAstroInteractionTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AAstroInteractionTrigger::OnOverlapEnd);
}

void AAstroInteractionTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerResponseObject)
	{
		TriggerResponseObject->K2_OnObjectActive();
	}

}

void AAstroInteractionTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(TriggerResponseObject) 
	{
		TriggerResponseObject->K2_OnObjectDeactive();
	}
}
