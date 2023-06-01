// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstroDefinition.h"
#include "MissionManagementComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FMissionClearCheckerDelegate, FName);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnMissionClearCheck, class UAstroMissionBase*, FName);


USTRUCT(BlueprintType)
struct FMissionChecker {

	GENERATED_BODY()

	FMissionChecker() {}

	FMissionChecker(const FOnMissionClearCheck& InMissionClearChecker) : MissionClearCheck(InMissionClearChecker) {}

	FOnMissionClearCheck MissionClearCheck;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UMissionManagementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMissionManagementComponent();

	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;
	
	//Mission Clear Check Functions
public :
	void InMissionIDEventOccured(FName InID);

private:

	UPROPERTY()
	TObjectPtr<class UAstroMissionBase> FrontwardMission;

	UPROPERTY()
	TObjectPtr<class UAstroMissionBase> BackwardMission;

	UPROPERTY()
	TArray<FName> MissionClearedList;

	//Mission Clear Check Functions

protected:
	//BroadCast Delegate
	FMissionClearCheckerDelegate MissionClearChecker;

	void FrontwardMissionClearChecker(FName InID);

	void FrontwardMissionSetter();

	void FrontwardGameStateSetter();

	void BackwardMissionClearChecker(FName InID);

	void BackwardMissionSetter();

	void BackwardGameStateSetter();

	//When Mission is cleared this function will called.
	void MissionClearedEvent(FName InID);

	FTimer TimerHandle;

	//Mission Clear Delegate
protected:
	UPROPERTY()
	TMap<EMissionType, FMissionChecker> MissionClearCheckEvent;

	bool InteractiveMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID);

	bool WaitMissionClearCheck(UAstroMissionBase* MissionBase, FName InObjID);
};
