// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstralBoxComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UAstralBoxComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAstralBoxComponent();

public :
	// Called when the game starts
	virtual void BeginPlay() override;

	FORCEINLINE bool SetActable(bool InBoolean) {
		bActable = InBoolean;
		return bActable;
	}

	FORCEINLINE bool GetCompleted() { return bCompleted; }

	float SettingPercent(float Percent);

	float Percentage;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	bool bActable;
	bool bCompleted;
	float CountTime = 1.5f;
	const float ConstTime = 1.5f;
};
