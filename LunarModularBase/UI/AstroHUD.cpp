// Fill out your copyright notice in the Description page of Project Settings.

#include "AstroHUD.h"

//Adding Header File
#include "UI/Mission/MissionWidget.h"
#include "UI/AstroPlayer/AstroCharacterWidget.h"
#include "UI/AstroInteractionObj/AstralBoxWidget.h"
#include "UI/Inventory/InventoryWidget.h"

#include "Item/AstroItemData.h"

AAstroHUD::AAstroHUD()
{
	static ConstructorHelpers::FClassFinder<UMissionWidget> MISSION_UI_CLASS(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/MissionWidget.MissionWidget_C'"));
	static ConstructorHelpers::FClassFinder<UAstroCharacterWidget> ASTRO_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UserStatusWidget.UserStatusWidget_C'"));
	static ConstructorHelpers::FClassFinder<UInventoryWidget> ASTRO_INVEN_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_Inventory.ASTRO_Inventory_C'"));
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
	}
}

void AAstroHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AAstroHUD::UpdateMissionText(FString& MissionText) 
{
	if (MissionWidget)
	{
		MissionWidget->UpdateMissionWidget(MissionText);
	}
}

void AAstroHUD::UpdateMissionScriptText(FString& MissionScript)
{
	if(MissionWidget) {
		MissionWidget->UpdateMissionScript(MissionScript);
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

	if(InItemData != nullptr)
		InventoryWidget->AddItemData(InItemData);
}


void AAstroHUD::ActiveItemWidget()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible) {
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayerController()->bShowMouseCursor = false;
	}
	else 
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayerController()->bShowMouseCursor = true;
	}
}


bool AAstroHUD::ItemContainCheck(UObject* InItemData)
{
	return InventoryWidget->IsItemContains(InItemData);
}
