// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AstroInstallItem.h"
#include "Item/AstroItemDatas.h"
#include "Net/UnrealNetwork.h"

void AAstroInstallItem::Initialize(UAstroActiveItemData* InItemData)
{
	if (InItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *InItemData->InstallationGroundMesh->GetName())
		ActivationItemData = InItemData;;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("In Item Data Null"));
	}
}


void AAstroInstallItem::BeginPlay()
{
	Super::BeginPlay();
	if (ActivationItemData)
		Mesh->SetStaticMesh(ActivationItemData->InstallationGroundMesh.Get());
	else
		UE_LOG(LogTemp, Warning, TEXT("Item Is Not Valid"));
}

void AAstroInstallItem::SetMeshofItem()
{
	if (ActivationItemData->InstallationGroundMesh.IsPending())
	{
		ActivationItemData->InstallationGroundMesh.LoadSynchronous();
	}
	Mesh->SetStaticMesh(ActivationItemData->InstallationGroundMesh.Get());

	FVector LocationVector = GetActorLocation();
	float Height = Mesh->GetStaticMesh()->GetBounds().BoxExtent.Z;
	LocationVector.Z = Height;
	SetActorLocation(LocationVector);
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