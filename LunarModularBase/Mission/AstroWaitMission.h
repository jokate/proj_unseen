// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mission/AstroMissionBase.h"
#include "AstroWaitMission.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroWaitMission : public UAstroMissionBase
{
	GENERATED_BODY()
public :
	UAstroWaitMission();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName NeedToClear;

	virtual bool ClearCheck(FName ObjID) override;	

	void Initialize(FName InMissionID, const struct FMissionData MissionData, const struct FWaitMissionData WaitMissionData);

	virtual void Initialize(FName InMissionID, const struct FMissionData MissionData) override;
};
