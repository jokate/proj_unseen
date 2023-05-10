// Fill out your copyright notice in the Description page of Project Settings.


#include "AstralBoxComponent.h"

// Sets default values for this component's properties
UAstralBoxComponent::UAstralBoxComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bActable = false;
	Percentage = 0.0f;
	// ...
}


// Called when the game starts
void UAstralBoxComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
}


float UAstralBoxComponent::SettingPercent(float Percent)
{
	if (Percent == 0.0f) {
		Percentage = Percent;
		return Percentage;
	}

	if (Percentage < 1.0f) {
		Percentage += Percent;
		UE_LOG(LogTemp, Log, TEXT("COMPLETE ITER"));
	}
	else {
		bCompleted = true;
	}

	return Percentage;
}

// Called every frame
void UAstralBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



