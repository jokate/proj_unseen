// Fill out your copyright notice in the Description page of Project Settings.

#include "AstroHUD.h"

//Adding Header File
#include "UI/Mission/MissionWidget.h"
#include "UI/AstroPlayer/AstroCharacterWidget.h"
#include "UI/AstroInteractionObj/AstralBoxWidget.h"

AAstroHUD::AAstroHUD()
{
	static ConstructorHelpers::FClassFinder<UMissionWidget> MISSION_UI_CLASS(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/MissionWidget.MissionWidget_C'"));
	static ConstructorHelpers::FClassFinder<UAstroCharacterWidget> ASTRO_WIDGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UserStatusWidget.UserStatusWidget_C'"));
	if (MISSION_UI_CLASS.Succeeded()) {
		MissionWidgetClass = MISSION_UI_CLASS.Class;
	}

	if (ASTRO_WIDGET.Succeeded()) {
		UserStatusClass = ASTRO_WIDGET.Class;
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
	}
}

void AAstroHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AAstroHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
