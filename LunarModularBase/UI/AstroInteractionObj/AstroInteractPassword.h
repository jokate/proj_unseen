// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/AstroWidgetInterface.h"
#include "AstroInteractPassword.generated.h"

/**
 * 
 */

UCLASS()
class LUNARMODULARBASE_API UAstroInteractPassword : public UUserWidget, public IAstroWidgetInterface
{
	GENERATED_BODY()
	

	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
	UFUNCTION(BlueprintCallable)
	void PasswordButtonPress(class UButton* InButton);

	UFUNCTION(BlueprintCallable)
	void EnterPress();

	UFUNCTION(BlueprintCallable)
	void CancelButtonPress();

	UFUNCTION(BlueprintCallable)
	void CloseButtonPress();

public :
	UFUNCTION(BlueprintCallable)
	virtual void OnVisible() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnInvisible() override;

public :
	UPROPERTY(BlueprintReadWrite)
	FString Password;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> PasswordText;

	FORCEINLINE void SetOwner(UActorComponent* InActor) 
	{
		Owner = InActor;
	}
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UActorComponent> Owner;

};
