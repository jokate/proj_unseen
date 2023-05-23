// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/AstroItemContainerObject.h"
#include "AstroInstallItem.generated.h"

class UAstroActiveItemData;
/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroInstallItem : public AAstroItemContainerObject
{
	GENERATED_BODY()
	
public :
	virtual void SetObjActiveComplete() override;

	void Initialize(UAstroActiveItemData* InItemData);

	virtual void BeginPlay() override;

	UFUNCTION()
	void SetMeshofItem();

public :
	UPROPERTY(ReplicatedUsing = SetMeshofItem, EditAnywhere, BlueprintReadWrite, Meta = (PrivateAccess = "true"), Category = ItemData)
	TObjectPtr<UAstroActiveItemData> ActivationItemData;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected :
};
