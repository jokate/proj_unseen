// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemComponent.h"
#include "Item/AstroActiveItemData.h"
#include "Item/AstroPassiveItemData.h"

#include "GameFrameWork/GameModeBase.h"
#include "GameFrameWork/HUD.h"

#include "Interface/AstroMissionManager.h"
#include "Interface/AstroHUDInterface.h"
#include "Net/UnrealNetwork.h"
// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	ItemUseEvents.Add((uint8)EActiveType::Operational, FUseItemDelegateWrapper(FOnUseItemDelegate::CreateUObject(this, &UItemComponent::OperateItem)));
	ItemUseEvents.Add((uint8)EActiveType::Installation, FUseItemDelegateWrapper(FOnUseItemDelegate::CreateUObject(this, &UItemComponent::OperateItem)));
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UItemComponent::ItemWidgetActive()
{
	auto PlayerHUD = Cast<IAstroHUDInterface>((GetWorld()->GetFirstPlayerController()->GetHUD()));
	if (PlayerHUD != nullptr && GetOwnerRole() == ENetRole::ROLE_AutonomousProxy) {
		PlayerHUD->ActiveItemWidget();
	}
}

void UItemComponent::InitItem(UAstroItemData* ItemData)
{	
	auto PlayerHUD = Cast<IAstroHUDInterface>((GetWorld()->GetFirstPlayerController()->GetHUD()));
	if (PlayerHUD != nullptr && GetOwnerRole() == ENetRole::ROLE_AutonomousProxy) {
		PlayerHUD->AddItem(ItemData);
	}
}

void UItemComponent::ItemUse(UAstroItemData* InItemData)
{
	if (InItemData->Type == EItemType::Active)
	{
		auto ItemData = CastChecked<UAstroActiveItemData>(InItemData);
		if (auto ItemUseEvent = ItemUseEvents.Find((uint8)ItemData->ActivationType))
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemActivated"));
			ItemUseEvent->ItemDeleagate.ExecuteIfBound(InItemData);
		}
	}

}

void UItemComponent::InstallItem(UAstroItemData* InItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Installed"));
	RequestMissionClearCheck(InItemData);
}

void UItemComponent::OperateItem(UAstroItemData* InItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Operated"));
	RequestMissionClearCheck(InItemData);
}

void UItemComponent::RequestMissionClearCheck_Implementation(UAstroItemData* InItemData)
{
	IAstroMissionManager* MissionManager = CastChecked<IAstroMissionManager>(GetWorld()->GetAuthGameMode());
	MissionManager->InMissionIDEventOccured(InItemData->ItemID);

}

