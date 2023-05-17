// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mission/AstroMissionBase.h"
#include "AstroInteractiveMission.generated.h"

/**
 * 
 */

UCLASS()
class LUNARMODULARBASE_API UAstroInteractiveMission : public UAstroMissionBase
{
	GENERATED_BODY()
	
public :
	UAstroInteractiveMission();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EInteractiveType InteractionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName MissionItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName NeedToClear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ActCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ActiveTime;

	int32 OriginalActCount;

	FTimerHandle ActivationTimer;

	//Clear Events
public :
	virtual bool ClearCheck(FName ObjID) override;

	void OnTimerUnCleared();

	//Initializer
public :

	void Initialize(FName InMissionID, const struct FMissionData MissionData, const struct FInteractiveMissionData InteractiveMissionData);

	virtual void Initialize(FName InMissionID, const struct FMissionData MissionData) override;
};
