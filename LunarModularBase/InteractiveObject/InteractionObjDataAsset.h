// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InteractionObjDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UInteractionObjDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> MeshData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UUserWidget> BoxCountWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D InteracionDrawSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector RelativeLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SphereRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ObjectID;

};
