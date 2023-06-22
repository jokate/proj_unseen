// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/InteractiveObject/AstroInteractableObject.h"
#include "Interface/AstroPwInteractInterface.h"
#include "AstroTriggerInteractiveObjectPW.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroTriggerInteractiveObjectPW : public AAstroInteractableObject, public IAstroPwInteractInterface {

	GENERATED_BODY()
	
	AAstroTriggerInteractiveObjectPW();
	
	virtual void BeginPlay() override;
public : 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Password)
	TObjectPtr<class UInteractivePasswordComponent> PasswordComponent;

protected  :
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "OnPasswordEnteredCompletelyCPP"))
	void K2_OnPasswordEnteredCompletely();

	virtual bool ComparePassword(const FString& InPassword);

	virtual void SetPercentage(float Infloat) override;
};
