// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractObjInterface.h"
#include "AstralBox.generated.h"

UCLASS()
class LUNARMODULARBASE_API AAstralBox : public AActor, public IInteractObjInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstralBox(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	//Collision Detected
	//UFUNCTION(Client, Reliable)
	virtual void SetObjActiveComplete() override;

	virtual void OnActivating() override;

	virtual void StopActivating() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	UPROPERTY(VisibleAnywhere, Category = CollisionPlayer)
	TObjectPtr<class AActor> Player;

	UPROPERTY(EditAnywhere)
	bool bIsComplete;
	FTimerHandle ActivationTimer;

	UPROPERTY(EditAnywhere)
	FName ObjectID = "";
	

private :
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
