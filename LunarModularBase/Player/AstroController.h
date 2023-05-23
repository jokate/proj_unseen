// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/StreamableManager.h"
#include "AstroController.generated.h"


/**

 * 
 */
struct FInputActionValue;

UCLASS(config=AstroCharacter)
class LUNARMODULARBASE_API AAstroController : public APlayerController 
{
	
	GENERATED_BODY()
	
public : 
	AAstroController(const FObjectInitializer& ObjectInitializer  = FObjectInitializer::Get());

protected :
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void SetupInputComponent() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
