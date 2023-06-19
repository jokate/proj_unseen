// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject/Trigger/AstroTriggerInteractiveObject.h"
#include "Interface/AstroPwInteractInterface.h"
#include "AstroTriggerInteractiveObjectPW.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API AAstroTriggerInteractiveObjectPW : public AAstroTriggerInteractiveObject, public IAstroPwInteractInterface
{
	GENERATED_BODY()
	
	AAstroTriggerInteractiveObjectPW();
	

	virtual void SetObjActiveComplete() override;

	virtual void BeginPlay() override;

	virtual void SetPercentage(float Infloat) override;

protected  :
	UPROPERTY()
	TSubclassOf<class UAstroInteractPassword> PasswordClass;

	UPROPERTY(VisibleAnywhere, Category = PasswordWidget)
	TObjectPtr<UAstroInteractPassword> PasswordWidget;

	UPROPERTY(EditAnywhere, Category = PassWord, meta = (PrivateAccess = "true"))
	FString PasswordString;

	virtual bool ComparePassword(const FString& InPassword) override;

	virtual AActor* ReturnTriggerObject() override 
	{
		return TriggerObject;
	}

};
