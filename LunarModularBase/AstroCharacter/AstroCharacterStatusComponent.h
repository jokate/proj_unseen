// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Components/ActorComponent.h"
#include "AstroCharacterStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UAstroCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAstroCharacterStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetExploring(bool InBoolean);
	
	bool& GetExplore() { return bExploring; }

	uint32& GetHP() { return Hp; }

	FTimerHandle HPHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	bool bSearch = false;

private:

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	bool bExploring = false;	


	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	uint32 Hp = 100;

};
