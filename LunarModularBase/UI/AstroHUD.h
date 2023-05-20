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
class UInventoryWidget;

UCLASS()
class LUNARMODULARBASE_API AAstroHUD : public AHUD, public IAstroHUDInterface
{
	GENERATED_BODY()
public:
	AAstroHUD();

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	//HUD Setting Function
public :
	virtual void UpdateMissionText(FString& MissionText) override;

	virtual void UpdateMissionScriptText(FString& MissionScript) override;

	UFUNCTION()
	virtual void SetVisibleUserStatus(bool& InVisible) override;
	UFUNCTION()
	virtual	void SetPlayerHPText(uint32& InHp) override;

	virtual void AddItem(UObject* InItemData) override;

	virtual void RemoveItem(UObject* InItemData) override;

	virtual void ActiveItemWidget() override;

	virtual void TextUpdateWhenHovered(class UAstroItemData* InItemData) override;

	virtual void TextUpdateWhenUnHovered() override;

	virtual bool ItemContainCheck(UObject* InItemData) override;

public :
	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
	TSubclassOf<UMissionWidget> MissionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
	TSubclassOf<UAstroCharacterWidget> UserStatusClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Widget")
	TSubclassOf<UInventoryWidget> InventoryClass;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
	TObjectPtr<UMissionWidget> MissionWidget;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
	TObjectPtr<UAstroCharacterWidget> UserStatusWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Widget")
	TObjectPtr<UInventoryWidget> InventoryWidget;
};
