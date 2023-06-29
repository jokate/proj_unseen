// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractableObjectInterface.h"
#include "AstroTriggerResponseObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectForSequencer);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectForSequencerGlobal);

UCLASS()
class LUNARMODULARBASE_API AAstroTriggerResponseObject : public AActor, public IInteractableObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstroTriggerResponseObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NeedToTrigger)
	TArray<class AAstroInteractionTrigger*> NeedToTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IsActivated)
	uint8 bIsActivated : 1;

public :


	UFUNCTION(BlueprintCallable)
	virtual void CheckActivationByTrigger();

	UFUNCTION(BlueprintCallable)
	virtual void SetObjActiveComplete() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetObjDeActivateComplete();
public:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnObjectActiveCPP"))
	void K2_OnObjectActive();


	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnObjectDeactiveCPP"))
	void K2_OnObjectDeactive();

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite,  Category = Interaction)
	FOnObjectForSequencer ForSequencer;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = Interaction)
		FOnObjectForSequencerGlobal ForGlobalSequencer;
	UFUNCTION(BlueprintCallable)
	virtual void SetTriggerEnable() override {}

};
