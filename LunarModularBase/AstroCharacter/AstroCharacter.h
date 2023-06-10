// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AstroCharacterInterface.h"
#include "Interface/AstroMissionClearInterface.h"
#include "Interface/AstroItemInterface.h"
#include "AstroCharacter.generated.h"


UCLASS()
class LUNARMODULARBASE_API AAstroCharacter : public ACharacter, public IAstroCharacterInterface, public IAstroMissionClearInterface, public IAstroItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAstroCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InputSystemInit();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	void ExploreWidgetVisibleSet(bool OnVisible);


	//On Collision To Object
public:
	FOnCharacterActivateObject OnActivateEvent;
	FOnCharacterStopActivateObject OnDeActivateEvent;

	virtual FOnCharacterActivateObject& ReturnActivateObjectDelegate() override;

	virtual FOnCharacterStopActivateObject& ReturnDeactivateObjectDelegate() override;

	virtual void OnMissionObjectCollided(FOnActivatedComplete& InActivaedDelegate) override;

	virtual void OnItemObjectCollided(FOnTakeItemDelegate& ItemDelegate) override;
public:

	UPROPERTY(VisibleAnywhere, Category = Camera)
		TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, Category = Status)
		TObjectPtr<class UAstroCharacterStatusComponent> CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = HUD)
		TObjectPtr<class AHUD> AstroHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EquippedItem, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> OnHandedItem;

public:
	//Move
	virtual void Move(const FInputActionValue& Value) override;
	virtual void LookUp(const FInputActionValue& Value) override;
	virtual void Turn(const FInputActionValue& Value) override;
	virtual void Swift(const FInputActionValue& Value) override;
	virtual void StopSwift(const FInputActionValue& Value) override;
	virtual void Exploring(const FInputActionValue& Value) override;
	virtual void UnExploring(const FInputActionValue& Value) override;

	//MissionClear Part
protected:
	UPROPERTY(VisibleAnywhere, Meta = (PrivateAccess = "true"))
		TObjectPtr<class UMissionComponent> MissionComponent;

	virtual void Req_MissionClear(FName ObjectName) override;

	virtual EPlayerType ReturnTag() override;

	virtual EPlayerType GetLocalPlayerTag() override;

	virtual void PlayerTypeSetting(EPlayerType InPlayerType) override;

	virtual void HUDUpdate(FName InMissionID);


public:

	void Search(const FInputActionValue& Value);

	void UnSearch(const FInputActionValue& Value);

	virtual void ActivationComplete(AActor* InActor) override;

	UFUNCTION(Server, Reliable)
		void ActivationComplete_Server(AActor* InActor);

	UFUNCTION(NetMulticast, Reliable)
		void ActivationComplete_Multicast(AActor* InActor);

	UFUNCTION(NetMulticast, Reliable)
		void ActivationComplete_Client(AActor* InActor);

	void ReactivateMissionWidget();

	void ExploreCheck(float DeltaTime);

protected:
	void SetControlMode();

	float ArmLengthTo = 450.0f;
	FRotator ArmRotatorTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

	//Relicated Variable and Event
protected:
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
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UMovementDataAsset* InputActions;

	//Item Section
protected:
	UPROPERTY(VisibleAnywhere, Category = "Item Component", Meta = (PrivateAccess = "true"))
		TObjectPtr<class UItemComponent> ItemComponent;

	void ActiveItemWidget();

	virtual void TakeItem(class UAstroItemData* InItemData) override;

	virtual void UseItem(class UAstroItemData* InItemData) override;

	virtual bool ContainsItem(UAstroItemData* ItemData) override;

	//Item RPC Calls
protected:

	virtual void ItemEquip(UAstroActiveItemData* InItemData) override;

	UFUNCTION(Server, Reliable)
		virtual void ItemEquip_Server(UAstroActiveItemData* InItemData);

	UFUNCTION(NetMulticast, Reliable)
		void ItemEquip_Multicast(UAstroActiveItemData* InItemData);

	UFUNCTION(Server, Reliable)
		virtual void ItemDeEquip(bool CanDequip) override;

	UFUNCTION(NetMulticast, Reliable)
		void ItemDeEquip_Server(bool CanDequip);

	void ItemInstall(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ItemInstall_Server();



	//For Item Installation
protected:
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
		TObjectPtr<UAstroActiveItemData> OnHandedItemData;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	TObjectPtr<UAstroActiveItemData> ToBeInstalled;


	UPROPERTY(EditAnywhere, Category = ItemInstallClass, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AAstroInstallItem> ItemInstallClass;

protected:

};
