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
class UAstroItemData;
class UInventoryWidget;
class UAstroInteractPassword;

UCLASS()
class LUNARMODULARBASE_API AAstroHUD : public AHUD, public IAstroHUDInterface
{
	GENERATED_BODY()
public:
	AAstroHUD();

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	//HUD Setting Function
public:
	virtual void UpdateMissionText(FString& MissionScript) override;

	virtual void UpdateMissionDialogText(const TArray<FString>& InStrings) override;

	virtual void ReactivateMissionText() override;

	UFUNCTION()
		virtual void SetVisibleUserStatus(bool& InVisible) override;
	UFUNCTION()
		virtual	void SetPlayerHPText(uint32& InHp) override;

	virtual void AddItem(UObject* InItemData) override;

	virtual void ActiveItemWidget() override;

	virtual void ItemUsed(UAstroItemData* InItemData) override;

	virtual bool ItemContainCheck(UAstroItemData* InItemData) override;

	virtual void SetPasswordVisible(AActor* InOwner) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
		TSubclassOf<UMissionWidget> MissionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
		TSubclassOf<UAstroCharacterWidget> UserStatusClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Widget")
		TSubclassOf<UInventoryWidget> InventoryClass;

	UPROPERTY(EditDefaultsOnly, Category = "Password Widget")
		TSubclassOf<UAstroInteractPassword> PasswordClass;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
		TObjectPtr<UMissionWidget> MissionWidget;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
		TObjectPtr<UAstroCharacterWidget> UserStatusWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Widget")
		TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Password Widget")
		TObjectPtr<UAstroInteractPassword> PasswordWidget;	
};
