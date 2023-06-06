// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstroDefinition.h"
#include "MissionComponent.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FOnObjectValidate, FName)

USTRUCT(BlueprintType)
struct FObjectValidateWrapper {
	GENERATED_BODY()

		FObjectValidateWrapper() {};
	FObjectValidateWrapper(const FOnObjectValidate& InObjectValidate) : ObjectValidate(InObjectValidate) {}

	FOnObjectValidate ObjectValidate;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LUNARMODULARBASE_API UMissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMissionComponent();

public:

	void Init();

	virtual void BeginPlay() override;

	FORCEINLINE void SetPlayerType(EPlayerType InPlayerType) { PlayerType = InPlayerType; }

	UFUNCTION(Server, Reliable)
		void ClearCheck(FName ObjectName);

	FORCEINLINE EPlayerType GetPlayerType() { return PlayerType; }

	//Validate Checker
protected:
	UPROPERTY()
		TMap<EPlayerType, FObjectValidateWrapper> ValidateEvents;

	//HUD CODE
public:
	void MissionHUDUpdate(FName InMissionID);

	void MissionDescriptionUpdate(FName InMissionID);

	void MissionClearScriptUpdate(FName InMissionID);
protected:
	UPROPERTY(VisibleAnywhere)
		EPlayerType PlayerType;


};
