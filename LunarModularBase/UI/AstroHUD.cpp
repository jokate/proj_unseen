// Fill out your copyright notice in the Description page of Project Settings.

#include "AstroHUD.h"

//Adding Header File
#include "UI/Mission/MissionWidget.h"
#include "UI/AstroPlayer/AstroCharacterWidget.h"
#include "UI/AstroInteractionObj/AstralBoxWidget.h"
#include "UI/Mission/ImageBoardingWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "UI/AstroInteractionObj/AstroInteractPassword.h"
#include "UI/SpectatingWidget.h"
#include "Item/AstroItemData.h"

AAstroHUD::AAstroHUD()
{
	static ConstructorHelpers::FClassFinder<UMissionWidget> MISSION_UI_CLASS(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/MissionWidget.MissionWidget_C'"));
	static ConstructorHelpers::FClassFinder<UAstroCharacterWidget> ASTRO_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UserStatusWidget.UserStatusWidget_C'"));
	static ConstructorHelpers::FClassFinder<UInventoryWidget> ASTRO_INVEN_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_Inventory.ASTRO_Inventory_C'"));
	static ConstructorHelpers::FClassFinder<UAstroInteractPassword> ASTRO_PASSWORD_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_Password.ASTRO_Password_C'"));
	static ConstructorHelpers::FClassFinder<UImageBoardingWidget> ASTRO_IMAGE_BOARD_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_IMAGE_BOARDER.ASTRO_IMAGE_BOARDER_C'"));
	static ConstructorHelpers::FClassFinder<USpectatingWidget> ASTRO_SPECTATING_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/ASTRO_SPECTATOR.ASTRO_SPECTATOR_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> ASTRO_AIM_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/AimPoint.AimPoint_C'"));
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

	if(ASTRO_IMAGE_BOARD_WIDGET.Class) 
	{
		ImageBoardClass = ASTRO_IMAGE_BOARD_WIDGET.Class;
	}

	if (ASTRO_SPECTATING_WIDGET.Class)
		SpectatingClass = ASTRO_SPECTATING_WIDGET.Class;

	if (ASTRO_AIM_WIDGET.Class)
		AimWidgetClass = ASTRO_AIM_WIDGET.Class;
	
}

void AAstroHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerController = GetOwningPlayerController();
	if (IsValid(MissionWidgetClass) && IsValid(UserStatusClass))
	{
		AimWidget = CreateWidget<UUserWidget>(PlayerController, AimWidgetClass);
		AimWidget->AddToViewport();
		SpectatingWidget = CreateWidget<USpectatingWidget>(PlayerController, SpectatingClass);
		SpectatingWidget->AddToViewport();
		UserStatusWidget = CreateWidget<UAstroCharacterWidget>(PlayerController, UserStatusClass);
		UserStatusWidget->AddToViewport();
		InventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryClass);
		InventoryWidget->AddToViewport();
		PasswordWidget = CreateWidget<UAstroInteractPassword>(PlayerController, PasswordClass);
		PasswordWidget->AddToViewport();
		ImageBoardWidget = CreateWidget<UImageBoardingWidget>(PlayerController, ImageBoardClass);
		ImageBoardWidget->AddToViewport();
		MissionWidget = CreateWidget<UMissionWidget>(PlayerController, MissionWidgetClass);
		MissionWidget->AddToViewport();
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

		if(SpectatingWidget->GetVisibility() == ESlateVisibility::Visible) {
			SetVisibilityOnSpectating();
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

		GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayerController()->bShowMouseCursor = false;
;		GetOwningPlayerController()->SetIgnoreLookInput(false);
	}
	else
	{
		GetOwningPlayerController()->SetInputMode(FInputModeGameAndUI());
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

void AAstroHUD::SetPasswordVisible(UActorComponent* InOwner)
{

	if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible) {
		ActiveItemWidget();
	}

	if (SpectatingWidget->GetVisibility() == ESlateVisibility::Visible) {
		SetVisibilityOnSpectating();
	}

	GetOwningPlayerController()->SetInputMode(FInputModeUIOnly());

	PasswordWidget->SetVisibility(ESlateVisibility::Visible);
	PasswordWidget->SetOwner(InOwner);
	SpectatingWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AAstroHUD::DialogStringOnBoard(const TArray<FString>& InString)
{
	if(!InString.IsEmpty()) 
	{
		MissionWidget->DialogStringOnBoard(InString);
		SpectatingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AAstroHUD::ImageWidgetSet(UTexture2D* InTexture)
{
	if(InTexture) 
	{
		if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible) {
			ActiveItemWidget();
		}

		if (SpectatingWidget->GetVisibility() == ESlateVisibility::Visible) {
			SetVisibilityOnSpectating();
		}

		GetOwningPlayerController()->SetInputMode(FInputModeUIOnly());
		ImageBoardWidget->ImageWidgetOnBoard(InTexture);
		SpectatingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AAstroHUD::SetVisibilityOnSpectating()
{
	SpectatingWidget->VisibilityButtonPressed();
}

void AAstroHUD::SetMaterialOnImageBoard(UMaterial* InMaterial)
{
	if(InMaterial) 
	{
		ImageBoardWidget->ImageWidgetMaterialChange(InMaterial);
	}
}
