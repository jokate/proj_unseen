// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/AstroTriggerResponseObject.h"
#include "Interface/InteractableObjectInterface.h"
#include "AstroInteractableObject.generated.h"

UCLASS()
class LUNARMODULARBASE_API AAstroInteractableObject : public AAstroTriggerResponseObject, public IInteractableObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstroInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PostInitializeComponents();

	//Basic Component
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UWidgetComponent> ActivationWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AccessChecker)
	TObjectPtr<class UAccessControlComponent> AccessChecker;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
	TObjectPtr<class USphereComponent> ObjectTrigger;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//Object Activation
protected :

	virtual void SetObjActiveComplete() override;

	virtual void OnActivating();

	virtual void StopActivating();
	
	//Activation Setter
protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ActivationPercent = 0.0f;

	const float ActivateIncreasePercentage = 0.05f;

	const float ActivationFullPercent = 1.0f;

	FTimerHandle ActivationTimer;

	UFUNCTION(BlueprintCallable)
	void SetPercentage(float Infloat);

	//For BlueprintEventFunction
public :

	//Overlap Function
protected :
	UFUNCTION()
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
