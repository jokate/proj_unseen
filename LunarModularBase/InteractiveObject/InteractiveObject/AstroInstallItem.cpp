// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroInstallItem.h"
#include "Item/AstroItemDatas.h"
#include "Interface/InteractionWidgetInterface.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "InteractiveObject/Components/InteractiveItemController.h"

void AAstroInstallItem::Initialize(UAstroActiveItemData* InItemData)
{
	if (InItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *InItemData->InstallationGroundMesh->GetName())
		ActivationItemData = InItemData;
		if (HasAuthority()) 
		{
			if (ActivationItemData->InstallationGroundMesh.IsPending())
			{
				ActivationItemData->InstallationGroundMesh.LoadSynchronous();
			}
			Mesh->SetStaticMesh(ActivationItemData->InstallationGroundMesh.Get());
			FVector LocationVector = GetActorLocation();
			float Height = LocationVector.Z;
			LocationVector.Z = Height;
			SetActorLocation(LocationVector);
		}

	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("In Item Data Null"));
	}
}


void AAstroInstallItem::BeginPlay()
{
	Super::BeginPlay();
	ItemComponent->ObjectItemData = ActivationItemData;
}

void AAstroInstallItem::SetMeshofItem()
{
	if (ActivationItemData->InstallationGroundMesh.IsPending())
	{
		ActivationItemData->InstallationGroundMesh.LoadSynchronous();
	}
	Mesh->SetStaticMesh(ActivationItemData->InstallationGroundMesh.Get());
}

void AAstroInstallItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAstroInstallItem, ActivationItemData);

}

void AAstroInstallItem::SetPercentage(float Infloat)
{
	ActivationPercent = Infloat;
	IInteractionWidgetInterface* Widget = Cast<IInteractionWidgetInterface>(ActivationWidget->GetWidget());
	if (Widget) {
		Widget->SetPercentage(ActivationPercent);
		if (ActivationPercent > ActivationFullPercent)
		{
			SetObjActiveComplete();
			K2_OnObjectActiveOnClient();
			ItemComponent->ReturnItem();
			GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
			SetPercentage(0.0f);
		}
	}
}

AAstroInstallItem::AAstroInstallItem()
{
	ItemComponent = CreateDefaultSubobject<UInteractiveItemController>("ITEM_COMPONENT");
}

void AAstroInstallItem::SetObjActiveComplete()
{
	AAstroInteractableObject::SetObjActiveComplete();
	Destroy();
}