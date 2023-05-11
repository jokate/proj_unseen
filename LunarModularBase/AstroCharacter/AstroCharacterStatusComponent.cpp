// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacterStatusComponent.h"

// Sets default values for this component's properties
UAstroCharacterStatusComponent::UAstroCharacterStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UAstroCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(HPHandle, [&]() {
		--Hp;
	}, 15.0f, true);

	// ...
	
}

void UAstroCharacterStatusComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UAstroCharacterStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAstroCharacterStatusComponent::SetExploring(bool InBoolean) 
{
	bExploring = InBoolean;
}
