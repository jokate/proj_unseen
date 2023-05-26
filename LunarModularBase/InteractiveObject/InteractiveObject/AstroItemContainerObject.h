// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "Interface/AstroItemInterface.h"
#include "AstroItemContainerObject.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroItemContainerObject : public AAstroInteractableObject
{
	GENERATED_BODY()
	
public :
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void SetObjActiveComplete() override;



protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (PrivateAccess = "true"), Category = ItemData)
	TObjectPtr<class UAstroItemData> ObjectItemData;

	FOnTakeItemDelegate OnItemIsGiven;

protected :

	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
