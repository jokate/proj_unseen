// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AstroPwInteractInterface.h"
#include "InteractivePasswordComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UInteractivePasswordComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractivePasswordComponent();

public:
	UPROPERTY(EditAnywhere, Category = PassWord, meta = (PrivateAccess = "true"))
	FString PasswordString;

	UFUNCTION(BlueprintCallable)
	void PasswordWidgetOnBoard();


		
};
