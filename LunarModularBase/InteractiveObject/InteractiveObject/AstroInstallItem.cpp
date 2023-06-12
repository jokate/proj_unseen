// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/InteractiveObject/AstroInstallItem.h"
#include "Item/AstroItemDatas.h"
#include "Net/UnrealNetwork.h"

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

void AAstroInstallItem::SetObjActiveComplete()
{
	OnItemIsGiven.ExecuteIfBound(ActivationItemData);
	AAstroInteractableObject::SetObjActiveComplete();
	Destroy();
}