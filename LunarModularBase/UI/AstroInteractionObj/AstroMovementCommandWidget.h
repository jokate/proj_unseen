// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/AstroWidgetInterface.h"
#include "AstroDefinition.h"
#include "AstroMovementCommandWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUNARMODULARBASE_API UAstroMovementCommandWidget : public UUserWidget, public IAstroWidgetInterface
{
	GENERATED_BODY()
	
public :
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UActorComponent> Owner;

	void SetOwner(UActorComponent* InOwner);

	UFUNCTION(BlueprintCallable)
	void MoveObject(EDirection MoveVector);

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnVisible() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnInvisible() override;

};
