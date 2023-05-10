// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AstroCharacterInterface.h"
#include "Interface/AstroMissionClearInterface.h"
#include "AstroCharacter.generated.h"


UCLASS()
class LUNARMODULARBASE_API AAstroCharacter : public ACharacter, public IAstroCharacterInterface, public IAstroMissionClearInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAstroCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual void SearchObjectHit(AActor* Obj, bool bInAndOut) override;

	void ExploreWidgetVisibleSet(bool OnVisible);

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, Category = Status)
	TObjectPtr<class UAstroCharacterStatusComponent> CharacterStat;
	
	UPROPERTY(VisibleAnywhere, Category = ContactedBox)
	TArray<AActor*> HitObj;

	UPROPERTY(VisibleAnywhere, Category = HUD)
	TObjectPtr<class AHUD> AstroHUD;

public:
	//Move
	virtual void UpDown(const FInputActionValue& Value) override;
	virtual void LeftRight(const FInputActionValue& Value) override;
	virtual void LookUp(const FInputActionValue& Value) override;
	virtual void Turn(const FInputActionValue& Value) override;
	virtual void Swift(const FInputActionValue& Value) override;
	virtual void StopSwift(const FInputActionValue& Value) override;
	virtual void Exploring(const FInputActionValue& Value) override;
	virtual void UnExploring(const FInputActionValue& Value) override;

	//MissionClear Part
protected :
	UPROPERTY(VisibleAnywhere, Meta = (PrivateAccess = "true"))
	TObjectPtr<class UMissionComponent> MissionComponent;

	virtual void Req_MissionClear(FName ObjectName) override;

	virtual EPlayerType ReturnTag() override;

	virtual void PlayerTypeSetting(EPlayerType InPlayerType) override;

	virtual void HUDUpdate(FName InMissionID);

	
public:
	//Jump / Search / MissionClear Check Function
	void Jumping(const FInputActionValue& Value);
	void Search(const FInputActionValue& Value);
	void UnSearch(const FInputActionValue& Value);
	void ExploreCheck(float DeltaTime);

	UObject* GetNearestObject();

protected:
	void SetControlMode();

	float ArmLengthTo = 450.0f;
	FRotator ArmRotatorTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

	//Relicated Variable and Event
protected :
	UPROPERTY(ReplicatedUsing = On_RepMovementSpeedUpdate)
	float MovementSpeed;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetMovementSpeed(float InSpeed);

	void OnMovementSpeedUpdate();

	UFUNCTION()
	void On_RepMovementSpeedUpdate();

	UFUNCTION(Server, Reliable)
	void Server_Swift(float InSpeed);

	//Input Actions
protected :

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UMovementDataAsset* InputActions;

};
