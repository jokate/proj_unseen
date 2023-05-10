// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AstroDefinition.h"
#include "Interface/AstroMissionManager.h"
#include "AstroGameState.generated.h"



UCLASS()
class LUNARMODULARBASE_API AAstroGameState : public AGameStateBase {
	GENERATED_BODY()
	
public :
	AAstroGameState();
	
	void SetFrontMissionID(FName InMissionID);

	void SetBackMissionID(FName InMissionID);

protected :

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	//Mission Update Event
protected :
	UFUNCTION()
	void FrontMissionIDUpdated();

	UFUNCTION()
	void BackMissionIDUpdated();

private:
	UPROPERTY(ReplicatedUsing = FrontMissionIDUpdated, VisibleAnywhere, Meta = (PrivateAccess = "true"))
	FName CurrentFrontMissionID;

	UPROPERTY(ReplicatedUsing = BackMissionIDUpdated, VisibleAnywhere, Meta = (PrivateAccess = "true"))
	FName CurrentBackMissionID;
};

