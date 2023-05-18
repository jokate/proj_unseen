// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/AstroInteractableObject.h"
#include "Interface/AstroMissionClearInterface.h"
#include "AstroMissionObject.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroMissionObject : public AAstroInteractableObject
{
	GENERATED_BODY()
	
public :
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void SetObjActiveComplete() override;

public :
	UPROPERTY(EditAnywhere)
	FName ObjectID = "";
	

public :
	FOnActivatedComplete OnActiveCompleted;

	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
