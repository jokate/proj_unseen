// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/AstroMissionClearInterface.h"
#include "AstralBox.generated.h"

UCLASS()
class LUNARMODULARBASE_API AAstralBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstralBox(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void SetObjActiveComplete();

	void OnActivating();

	void StopActivating();

	void VisibleSetting(bool InBoolean);

	void ActivationSetting(float Percentage);
public:	
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<UStaticMeshComponent> Box;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	TObjectPtr<class UAstralBoxComponent> BoxStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	TObjectPtr<class UWidgetComponent> ActivationWidget;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class USphereComponent> Trigger;

	//On Player Collision
public :
	FTimerHandle ActivationTimer;

	UPROPERTY(EditAnywhere)
	FName ObjectID = "";
	

protected :
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Item Section
protected :
	FOnActivatedComplete OnActiveCompleted;

	FOnTakeItemDelegate OnItemIsGiven;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (PrivateAccess = "true"), Category = ItemData)
	TObjectPtr<class UAstroItemData> ObjectItemData;

};
