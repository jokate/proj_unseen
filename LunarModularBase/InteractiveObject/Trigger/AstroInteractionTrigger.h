// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AstroInteractionTrigger.generated.h"

UCLASS()
class LUNARMODULARBASE_API AAstroInteractionTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstroInteractionTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AAstroTriggerResponseObject*> TriggerResponseObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TriggerVolume)
	TObjectPtr<class UBoxComponent> TriggerVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> ObjectMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = isTriggered)
	uint8 bIsTriggered : 1;

protected :

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
