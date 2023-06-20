// Fill out your copyright notice in the Description page of Project Settings.

#include "AstroHUD.h"

//Adding Header File
#include "UI/Mission/MissionWidget.h"
#include "UI/AstroPlayer/AstroCharacterWidget.h"
#include "UI/AstroInteractionObj/AstralBoxWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "UI/AstroInteractionObj/AstroInteractPassword.h"
#include "Item/AstroItemData.h"

AAstroHUD::AAstroHUD()
{
	static ConstructorHelpers::FClassFinder<UMissionWidget> MISSION_UI_CLASS(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/MissionWidget.MissionWidget_C'"));
	static ConstructorHelpers::FClassFinder<UAstroCharacterWidget> ASTRO_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UserStatusWidget.UserStatusWidget_C'"));
	static ConstructorHelpers::FClassFinder<UInventoryWidget> ASTRO_INVEN_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_Inventory.ASTRO_Inventory_C'"));
	static ConstructorHelpers::FClassFinder<UAstroInteractPassword> ASTRO_PASSWORD_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_Password.ASTRO_Password_C'"));
	if (ASTRO_PASSWORD_WIDGET.Class)
	{
		PasswordClass = ASTRO_PASSWORD_WIDGET.Class;
	}

	if (MISSION_UI_CLASS.Succeeded()) {
		MissionWidgetClass = MISSION_UI_CLASS.Class;
	}

	if (ASTRO_WIDGET.Succeeded()) {
		UserStatusClass = ASTRO_WIDGET.Class;
	}
	if (ASTRO_INVEN_WIDGET.Class)
	{
		InventoryClass = ASTRO_INVEN_WIDGET.Class;
	}

}

void AAstroHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerController = GetOwningPlayerController();
	if (IsValid(MissionWidgetClass) && IsValid(UserStatusClass))
	{
		MissionWidget = CreateWidget<UMissionWidget>(PlayerController, MissionWidgetClass);
		MissionWidget->AddToViewport();
		MissionWidget->SetVisibility(ESlateVisibility::Visible);
		UserStatusWidget = CreateWidget<UAstroCharacterWidget>(PlayerController, UserStatusClass);
		UserStatusWidget->AddToViewport();
		InventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryClass);
		InventoryWidget->AddToViewport();
		PasswordWidget = CreateWidget<UAstroInteractPassword>(PlayerController, PasswordClass);
		PasswordWidget->AddToViewport();
	}
}

void AAstroHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AAstroHUD::UpdateMissionText(FString& MissionScript)
{
	if (MissionWidget)
	{
		MissionWidget->UpdateMissionText(MissionScript);
	}
}

void AAstroHUD::UpdateMissionDialogText(const TArray<FString>& InStrings)
{
	if (MissionWidget) {
		if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible) {
			ActiveItemWidget();
		}
		GetOwningPlayerController()->bShowMouseCursor = false;
		MissionWidget->UpdateMissionDialogWidget(InStrings);
	}
}

void AAstroHUD::ReactivateMissionText()
{
	if (MissionWidget)
	{
		MissionWidget->ReactivateMissionTextBorder();
	}
}

void AAstroHUD::SetVisibleUserStatus(bool& InVisible)
{
	if (UserStatusWidget)
	{
		UserStatusWidget->ExploreUIActive(InVisible);
	}
}

void AAstroHUD::SetPlayerHPText(uint32& InHp)
{
	if (UserStatusWidget)
	{
		UserStatusWidget->HPTextUpdate(InHp);
	}
}

void AAstroHUD::AddItem(UObject* InItemData)
{
	ensure(InItemData);

	if (InItemData != nullptr)
		InventoryWidget->AddItemData(InItemData);
}


void AAstroHUD::ActiveItemWidget()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible) {
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayerController()->bShowMouseCursor = false;
		GetOwningPlayerController()->SetIgnoreLookInput(false);
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayerController()->bShowMouseCursor = true;
		GetOwningPlayerController()->SetIgnoreLookInput(true);
	}
}

void AAstroHUD::ItemUsed(UAstroItemData* InItemData)
{
	InventoryWidget->ItemCountDown(InItemData);
}


bool AAstroHUD::ItemContainCheck(UAstroItemData* InItemData)
{
	return InventoryWidget->IsItemContains(InItemData);
}

void AAstroHUD::SetPasswordVisible(AActor* InOwner)
{
	PasswordWidget->SetVisibility(ESlateVisibility::Visible);
	PasswordWidget->OnVisible();
	PasswordWidget->SetOwner(InOwner);
}
