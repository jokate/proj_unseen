// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacter.h"

#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AstroCharacterStatusComponent.h"
#include "AstroCharacter/AstroAnimInstance.h"
#include "Interface/InteractableObjectInterface.h"
#include "Interface/AstroHUDInterface.h"
#include "Interface/MovementCommandInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveObject/InteractiveObject/AstroInstallItem.h"

//Mission
#include "Mission/MissionComponent.h"

//Item Component
#include "Item/ItemComponent.h"
#include "Item/AstroItemDatas.h"

//For Movement 
#include "Kismet/GameplayStatics.h"
#include "MovementDataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

//UserData Assets
#include "UserDataAsset.h"

#include "Net/UnrealNetwork.h"
#include "Player/AstroController.h"


const float SwiftSpeed = 400.0f;
const float DefaultSpeed = 200.0f;
const float DefaultDistance = 450.0f;
const float ZoomInDistance = 350.0f;


// Sets default values
AAstroCharacter::AAstroCharacter()
{
	TObjectPtr<UUserDataAsset> UserDataAsset = nullptr;

	static ConstructorHelpers::FObjectFinder<UUserDataAsset> USER_DATA(TEXT("/Script/LunarModularBase.UserDataAsset'/Game/DataAsset/AstroCharacterAsset.AstroCharacterAsset'"));

	check(USER_DATA.Succeeded())

		if (USER_DATA.Succeeded()) {
			UserDataAsset = USER_DATA.Object;
		}

	check(UserDataAsset)

		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<UAstroCharacterStatusComponent>(TEXT("ASTROSTATUS"));
	MissionComponent = CreateDefaultSubobject<UMissionComponent>(TEXT("MISSION"));
	ItemComponent = CreateDefaultSubobject<UItemComponent>(TEXT("ITEM"));
	OnHandedItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ONHANDED"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCharacterMovement()->GravityScale = UserDataAsset->GravityScale;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	GetCharacterMovement()->JumpZVelocity = UserDataAsset->JumpZVelocity;

	GetMesh()->SetSkeletalMesh(UserDataAsset->AstroMesh);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	InputMapping = UserDataAsset->InputMappingContextAsset;
	InputActions = UserDataAsset->MovementDataAsset;

	OnHandedItem->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	GetMesh()->SetAnimInstanceClass(UserDataAsset->AnimInstance);

	SetControlMode();
	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("AstroCharacter"));
	ItemInstallClass = AAstroInstallItem::StaticClass();

	bReplicates = true;
}

// Called when the game starts or when spawned
void AAstroCharacter::BeginPlay()
{
	Super::BeginPlay();
	AstroHUD = GetWorld()->GetFirstPlayerController()->GetHUD();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
			Subsystem->AddMappingContext(InputMapping, 0);
	}

	GetWorld()->OnWorldBeginPlay.AddUObject(this, &AAstroCharacter::InputSystemInit);

}

void AAstroCharacter::InputSystemInit()
{
	//For Defending Error
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(Subsystem)
			Subsystem->AddMappingContext(InputMapping, 0);
	}

}


// Called every frame
void AAstroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ExploreCheck(DeltaTime);
}

// Called to bind functionality to input
void AAstroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent);
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AAstroCharacter::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AAstroCharacter::LookUp);
	PEI->BindAction(InputActions->InputTurn, ETriggerEvent::Triggered, this, &AAstroCharacter::Turn);
	PEI->BindAction(InputActions->InputExplore, ETriggerEvent::Triggered, this, &AAstroCharacter::Exploring);
	PEI->BindAction(InputActions->InputExplore, ETriggerEvent::Completed, this, &AAstroCharacter::UnExploring);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Triggered, this, &AAstroCharacter::Swift);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Completed, this, &AAstroCharacter::StopSwift);
	PEI->BindAction(InputActions->InputSearch, ETriggerEvent::Triggered, this, &AAstroCharacter::Search);
	PEI->BindAction(InputActions->InputSearch, ETriggerEvent::Completed, this, &AAstroCharacter::UnSearch);
	PEI->BindAction(InputActions->ItemUse, ETriggerEvent::Triggered, this, &AAstroCharacter::ActiveItemWidget);
	PEI->BindAction(InputActions->ItemInstall, ETriggerEvent::Triggered, this, &AAstroCharacter::ItemInstall);
	PEI->BindAction(InputActions->ReactivateMissionWidget, ETriggerEvent::Triggered, this, &AAstroCharacter::ReactivateMissionWidget);
	PEI->BindAction(InputActions->SpectatingViewButton, ETriggerEvent::Triggered, this, &AAstroCharacter::SpectatingViewButtonPressed);
}


void AAstroCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

#pragma region For Control

void AAstroCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector ScaledMovementInput = (ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X).GetSafeNormal();
		if (CharacterStat->bSearch) return;
		// add movement 

		AddMovementInput(ScaledMovementInput);
	}

}


void AAstroCharacter::LookUp(const FInputActionValue& Value)
{
	float NewAxisValue = Value.Get<float>();
	AddControllerPitchInput(-NewAxisValue);
}

void AAstroCharacter::Turn(const FInputActionValue& Value)
{
	float NewAxisValue = Value.Get<float>();
	AddControllerYawInput(NewAxisValue);
}

void AAstroCharacter::Swift(const FInputActionValue& Value)
{
	Server_Swift(SwiftSpeed);
}
void AAstroCharacter::StopSwift(const FInputActionValue& Value)
{
	Server_Swift(DefaultSpeed);
}

void AAstroCharacter::Search(const FInputActionValue& Value)
{
	OnActivateEvent.ExecuteIfBound();
}

void AAstroCharacter::UnSearch(const FInputActionValue& Value)
{
	OnDeActivateEvent.ExecuteIfBound();
}

void AAstroCharacter::ActivationComplete(AActor* InActor)
{
	ActivationComplete_Server(InActor);
}

void AAstroCharacter::MoveObject_Multicast_Implementation(AActor* InActor, EDirection MoveVector)
{
	auto NeedToMoveObject = CastChecked<IMovementCommandInterface>(InActor);
	NeedToMoveObject->MoveObject(MoveVector);
}

void AAstroCharacter::MoveObject_Implementation(AActor* InActor, EDirection MoveVector)
{
	MoveObject_Multicast(InActor, MoveVector);
}

void AAstroCharacter::ActivationComplete_Server_Implementation(AActor* InActor)
{
	ActivationComplete_Multicast(InActor);
}

void AAstroCharacter::ActivationComplete_Multicast_Implementation(AActor* InActor)
{
	IInteractableObjectInterface* InteractableObject = Cast<IInteractableObjectInterface>(InActor);
	if (InteractableObject)
	{
		InteractableObject->SetObjActiveComplete();
	}
}
void AAstroCharacter::ActivationComplete_Client_Implementation(AActor* InActor)
{
	if (!HasAuthority()) {
		IInteractableObjectInterface* InteractableObject = Cast <IInteractableObjectInterface>(InActor);
		if (InteractableObject)
		{
			InteractableObject->SetObjActiveComplete();
		}
	}
}


void AAstroCharacter::Exploring(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->Velocity.Z != 0.0f) return;

	ExploreWidgetVisibleSet(true);
}

void AAstroCharacter::UnExploring(const FInputActionValue& Value)
{
	ExploreWidgetVisibleSet(false);

}

void AAstroCharacter::SpectatingViewButtonPressed(const FInputActionValue& Value)
{
	auto PlayerHUD = Cast<IAstroHUDInterface>((GetWorld()->GetFirstPlayerController()->GetHUD()));
	if (PlayerHUD != nullptr) {
		PlayerHUD->SetVisibilityOnSpectating();
	}
}



#pragma endregion

#pragma region Mission

void AAstroCharacter::Req_MissionClear(FName ObjectName)
{
	MissionComponent->ClearCheck(ObjectName);
}

EPlayerType AAstroCharacter::ReturnTag()
{
	return MissionComponent->GetPlayerType();
}

EPlayerType AAstroCharacter::GetLocalPlayerTag()
{
	AAstroController* AstroController = CastChecked<AAstroController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	return AstroController->CurrentPlayerType;
}

void AAstroCharacter::PlayerTypeSetting(EPlayerType InPlayerType)
{
	MissionComponent->SetPlayerType(InPlayerType);
}

void AAstroCharacter::HUDUpdate(FName InMissionID)
{
	MissionComponent->MissionHUDUpdate(InMissionID);
}


#pragma endregion



void AAstroCharacter::ReactivateMissionWidget()
{
	auto PlayerHUD = Cast<IAstroHUDInterface>((GetWorld()->GetFirstPlayerController()->GetHUD()));
	if (PlayerHUD != nullptr) {
		PlayerHUD->ReactivateMissionText();
	}
}

void AAstroCharacter::ExploreCheck(float DeltaTime)
{

	if (CharacterStat->GetExplore())
	{
		SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ZoomInDistance, DeltaTime, ArmLengthSpeed);
	}
	else
	{
		SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, DefaultDistance, DeltaTime, ArmLengthSpeed);
	}
}


void AAstroCharacter::SetControlMode() {
	SpringArm->TargetArmLength = DefaultDistance;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

}

#pragma region Speed Request
void AAstroCharacter::On_RepMovementSpeedUpdate()
{
	OnMovementSpeedUpdate();
}



void AAstroCharacter::OnMovementSpeedUpdate()
{
	//UE_LOG(LogTemp, Warning, TEXT("Speed : %f"), MovementSpeed);
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

}

void AAstroCharacter::Server_Swift_Implementation(float InSpeed)
{
	MovementSpeed = InSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

#pragma endregion

void AAstroCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAstroCharacter, MovementSpeed);
}


void AAstroCharacter::ExploreWidgetVisibleSet(bool InVisible)
{

}


FOnCharacterActivateObject& AAstroCharacter::ReturnActivateObjectDelegate()
{
	return OnActivateEvent;
}

FOnCharacterStopActivateObject& AAstroCharacter::ReturnDeactivateObjectDelegate()
{
	return OnDeActivateEvent;
}

void AAstroCharacter::OnMissionObjectCollided(FOnActivatedComplete& InActivatedDelegate)
{

}

void AAstroCharacter::OnItemObjectCollided(FOnTakeItemDelegate& ItemDelegate)
{
}

void AAstroCharacter::ActiveItemWidget()
{
	ItemComponent->ItemWidgetActive();
}

void AAstroCharacter::TakeItem(UAstroItemData* InItemData)
{
	ItemComponent->InitItem(InItemData);
}

void AAstroCharacter::UseItem(UAstroItemData* InItemData)
{
	UE_LOG(LogTemp, Log, TEXT("Item Use"));
	ItemComponent->ItemUse(InItemData);
}

bool AAstroCharacter::ContainsItem(UAstroItemData* ItemData)
{
	return ItemComponent->ItemContainCheck(ItemData);
}

void AAstroCharacter::ItemEquip(UAstroActiveItemData* InItemData)
{
	if (OnHandedItemData)
	{
		ItemComponent->InitItem(OnHandedItemData);
	}

	auto PlayerHUD = Cast<IAstroHUDInterface>((GetWorld()->GetFirstPlayerController()->GetHUD()));
	if (PlayerHUD != nullptr) {
		PlayerHUD->ItemUsed(InItemData);
	}

	ItemEquip_Server(InItemData);

}

void AAstroCharacter::ItemEquip_Multicast_Implementation(UAstroActiveItemData* InItemData)
{
	if (InItemData)
	{
		if (InItemData->InstallationGroundMesh.IsPending())
		{
			InItemData->InstallationGroundMesh.LoadSynchronous();
		}
		OnHandedItemData = InItemData;
		ToBeInstalled = OnHandedItemData;		
		OnHandedItem->SetStaticMesh(InItemData->InstallationGroundMesh.Get());

	}
}


void AAstroCharacter::ItemEquip_Server_Implementation(UAstroActiveItemData* InItemData)
{
	ItemEquip_Multicast(InItemData);
}

void AAstroCharacter::ItemDeEquip_Implementation(bool CanDequip)
{
	ItemDeEquip_Server(CanDequip);
}

void AAstroCharacter::ItemDeEquip_Server_Implementation(bool CanDequip)
{
	if (CanDequip) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Install Complete"));
		OnHandedItemData = nullptr;
		ToBeInstalled = nullptr;
		OnHandedItem->SetStaticMesh(nullptr);
	}
	else 
	{
		OnHandedItemData = ToBeInstalled;
		UE_LOG(LogTemp, Warning, TEXT("Item Install NonComplete"));
	}
}

void AAstroCharacter::ItemInstall(const FInputActionValue& Value)
{
	if (OnHandedItemData) {
		UE_LOG(LogTemp, Warning, TEXT("Item Install Initiate"));
		OnHandedItemData = nullptr;
		ItemInstall_Server();
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Install Cannot Be Initiated"));
	}
}

void AAstroCharacter::ItemInstall_Server_Implementation()
{
	const float MaxRadius = 300.0f;
	const float MinRadius = 100.0f;
	bool IsInstalled = false;
	FHitResult Hit;
	FVector Start = GetActorLocation();
	Start.Z += GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FVector End = Start + Camera->GetForwardVector() * FVector2D::Distance(FVector2D::ZeroVector, FVector2D(Start.Z, MaxRadius));
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FRotator CameraRotator = FRotator(0, Camera->GetComponentRotation().Yaw + 180.0f, 0);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, QueryParams);


	if (Hit.bBlockingHit)
	{

		UE_LOG(LogTemp, Warning, TEXT("Hit Object : %s"), *Hit.GetActor()->GetName())
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f);
		FVector HitPoint = Hit.ImpactPoint;
		FVector ForDistanceVector = GetActorLocation();
		ForDistanceVector.Z = HitPoint.Z;
		double Distance = FVector::Distance(HitPoint, ForDistanceVector);
		const FTransform SpawnTransform(CameraRotator, HitPoint);

		if (MinRadius <= Distance && Distance <= MaxRadius)
		{
			AAstroInstallItem* InstalledItem = GetWorld()->SpawnActorDeferred<AAstroInstallItem>(ItemInstallClass, SpawnTransform);

			InstalledItem->Initialize(ToBeInstalled);
			InstalledItem->FinishSpawning(SpawnTransform);
			IsInstalled = true;
		}
	}
	ItemDeEquip(IsInstalled);
}



