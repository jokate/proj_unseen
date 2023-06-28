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
class UImageBoardingWidget;
class USpectatingWidget;
class UAstroMovementCommandWidget;

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

	virtual void SetPasswordVisible(UActorComponent* InOwner) override;

	virtual void DialogStringOnBoard(const TArray<FString>& InString) override;

	virtual void ImageWidgetSet(class UTexture2D* InTexture) override;

	virtual void SetVisibilityOnSpectating() override;

	virtual void SetMovementCommandActive(UActorComponent* InActor) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
		TSubclassOf<UMissionWidget> MissionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
		TSubclassOf<UAstroCharacterWidget> UserStatusClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Widget")
		TSubclassOf<UInventoryWidget> InventoryClass;

	UPROPERTY(EditDefaultsOnly, Category = "Password Widget")
		TSubclassOf<UAstroInteractPassword> PasswordClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Image Board Widget")
		TSubclassOf<UImageBoardingWidget> ImageBoardClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spectating View")
	TSubclassOf<USpectatingWidget> SpectatingClass;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Command View")
	TSubclassOf<UAstroMovementCommandWidget> MovementCommandClass;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Mission Widget")
		TObjectPtr<UMissionWidget> MissionWidget;

	UPROPERTY(EditDefaultsOnly, Category = "User Status Widget")
		TObjectPtr<UAstroCharacterWidget> UserStatusWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Widget")
		TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Password Widget")
		TObjectPtr<UAstroInteractPassword> PasswordWidget;	

	UPROPERTY(EditDefaultsOnly, Category = "Image Board Widget")
		TObjectPtr<UImageBoardingWidget> ImageBoardWidget;


	UPROPERTY(EditDefaultsOnly, Category = "Spectating Widget")
	TObjectPtr<USpectatingWidget> SpectatingWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Spectating Widget")
	TObjectPtr<UAstroMovementCommandWidget> MovementCommandWidget;
};
