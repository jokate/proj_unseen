// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AstroDefinition.h"
#include "AstroMissionBase.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroMissionBase : public UObject
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName MissionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EMissionType MissionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName NextMissionID;

	virtual bool ClearCheck(FName ObjID);

	virtual void Initialize(FName InMissionID, const struct FMissionData MissionData);
};
