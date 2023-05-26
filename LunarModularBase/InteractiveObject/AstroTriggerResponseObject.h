// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AstroTriggerResponseObject.generated.h"

UCLASS()
class LUNARMODULARBASE_API AAstroTriggerResponseObject : public AActor
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

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnObjectActiveCPP"))
	void K2_OnObjectActive();


	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnObjectDeactiveCPP"))
	void K2_OnObjectDeactive();
};
