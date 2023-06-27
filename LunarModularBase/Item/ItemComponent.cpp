// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemComponent.h"
#include "Item/AstroItemDatas.h"

#include "GameFrameWork/GameModeBase.h"
#include "GameFrameWork/HUD.h"

#include "Interface/AstroMissionManager.h"
#include "Interface/AstroItemInterface.h"
#include "Interface/AstroHUDInterface.h"
#include "Net/UnrealNetwork.h"
// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemUseEvents.Add((uint8)EActiveType::PermanentOperational, FUseItemDelegateWrapper(FOnUseItemDelegate::CreateUObject(this, &UItemComponent::OperateItem)));
	ItemUseEvents.Add((uint8)EActiveType::Installation, FUseItemDelegateWrapper(FOnUseItemDelegate::CreateUObject(this, &UItemComponent::InstallItem)));
}

void UItemComponent::ItemWidgetActive()
{
	auto PlayerHUD = Cast<IAstroHUDInterface>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetHUD());;
	if (PlayerHUD != nullptr) {
		PlayerHUD->ActiveItemWidget();
	}
}

void UItemComponent::InitItem(UAstroItemData* ItemData)
{	
	if (!ItemData)
		return;
	auto PlayerHUD = Cast<IAstroHUDInterface>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetHUD());
	if (PlayerHUD != nullptr) {
		PlayerHUD->AddItem(ItemData);
	}
}

void UItemComponent::ItemUse(UAstroItemData* InItemData)
{
	auto ItemData = CastChecked<UAstroActiveItemData>(InItemData);
	if (auto ItemUseEvent = ItemUseEvents.Find((uint8)ItemData->ActivationType))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemActivated"));
		ItemUseEvent->ItemDeleagate.ExecuteIfBound(InItemData);
	}
}

void UItemComponent::InstallItem(UAstroItemData* InItemData)
{
	UAstroActiveItemData* ActiveItemData = CastChecked<UAstroActiveItemData>(InItemData);

	IAstroItemInterface* UserForItem = CastChecked<IAstroItemInterface>(GetOwner());
	UserForItem->ItemEquip(ActiveItemData);

	UE_LOG(LogTemp, Warning, TEXT("Item Installed"));
	RequestMissionClearCheck(InItemData);
}

void UItemComponent::OperateItem(UAstroItemData* InItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Operated"));
	RequestMissionClearCheck(InItemData);
}



bool UItemComponent::ItemContainCheck(UAstroItemData* InItemData)
{
	auto PlayerHUD = Cast<IAstroHUDInterface>((GetWorld()->GetFirstPlayerController()->GetHUD()));
	if (PlayerHUD != nullptr && GetOwnerRole() == ENetRole::ROLE_AutonomousProxy) {
		PlayerHUD->ItemContainCheck(InItemData);
	}
	return false;
}

void UItemComponent::RequestMissionClearCheck_Implementation(UAstroItemData* InItemData)
{
	IAstroMissionManager* MissionManager = CastChecked<IAstroMissionManager>(GetWorld()->GetAuthGameMode());
	MissionManager->InMissionIDEventOccured(InItemData->ItemID);

}

