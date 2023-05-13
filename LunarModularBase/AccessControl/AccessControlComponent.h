// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AccessControlComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UAccessControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAccessControlComponent();

public:
	bool CanBeActivated(AActor* InCharacterActor);

protected:
	bool GameStateChecker();

	bool PlayerItemChecker(AActor* InCharacterActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (PrivateAccess = "true"), Category = NeedToClearMission)
	TArray<FName> NeedMissionIDs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (PrivateAccess = "true"), Category = NeedToClearMission)
	FName NeedItemID;
		
};
