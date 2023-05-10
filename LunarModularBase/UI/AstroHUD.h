// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interface/AstroHUDInterface.h"
#include "AstroHUD.generated.h"

/**
 * 
 */
class UMissionWidget;
class UAstroCharacterWidget;

UCLASS()
class LUNARMODULARBASE_API AAstroHUD : public AHUD, public IAstroHUDInterface
{
	GENERATED_BODY()
public:
	AAstroHUD();

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void UpdateMissionText(FString& MissionText) override;

	UFUNCTION()
	virtual void UpdateMissionScriptText(FString& MissionScript) override;

	UFUNCTION()
	virtual void SetVisibleUserStatus(bool& InVisible) override;

	UFUNCTION()
	virtual	void SetPlayerHPText(uint32& InHp) override;

	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
	TSubclassOf<UMissionWidget> MissionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
	TSubclassOf<UAstroCharacterWidget> UserStatusClass;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
	TObjectPtr<UMissionWidget> MissionWidget;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
	TObjectPtr<UAstroCharacterWidget> UserStatusWidget;


};