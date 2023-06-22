// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "AstroInstallItem.generated.h"

class UAstroActiveItemData;
/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroInstallItem : public AAstroInteractableObject
{
	GENERATED_BODY()
	
public :
	AAstroInstallItem();

	virtual void SetObjActiveComplete() override;

	void Initialize(UAstroActiveItemData* InItemData);

	virtual void BeginPlay() override;

	UFUNCTION()
	void SetMeshofItem();

public :
	UPROPERTY(ReplicatedUsing = SetMeshofItem, EditAnywhere, BlueprintReadWrite, Meta = (PrivateAccess = "true"), Category = ItemData)
	TObjectPtr<UAstroActiveItemData> ActivationItemData;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetPercentage(float Infloat) override;
protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ItemComponent)
	TObjectPtr<class UInteractiveItemController> ItemComponent;
};
