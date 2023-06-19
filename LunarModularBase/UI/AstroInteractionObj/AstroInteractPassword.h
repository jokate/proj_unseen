// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AstroInteractPassword.generated.h"

/**
 * 
 */

UCLASS()
class LUNARMODULARBASE_API UAstroInteractPassword : public UUserWidget
{
	GENERATED_BODY()
	

	virtual void NativeConstruct();

	
	UFUNCTION(BlueprintCallable)
	void PasswordButtonPress(class UButton* InButton);

	UFUNCTION(BlueprintCallable)
	void EnterPress();

	UFUNCTION(BlueprintCallable)
	void CancelButtonPress();

	UFUNCTION(BlueprintCallable)
	void CloseButtonPress();

	void ClosingAction();

public :
	UPROPERTY(BlueprintReadWrite)
	FString Password;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> PasswordText;

	FORCEINLINE void SetOwner(AActor* Actor) 
	{
		Owner = Actor;
	}
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> Owner;

};
