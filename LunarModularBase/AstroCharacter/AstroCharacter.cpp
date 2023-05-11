// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroCharacter.h"

#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"

//For Widget
#include "AstroCharacterStatusComponent.h"
#include "Components/WidgetComponent.h"

//Mission
#include "Mission/MissionComponent.h"

//Item Component
#include "Item/ItemComponent.h"

//For Movement 
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MovementDataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Game/AstroPlayerState.h"

//Interface
#include "Interface/InteractObjInterface.h"

//UserData Assets
#include "UserDataAsset.h"
#include "Net/UnrealNetwork.h"


const float SwiftSpeed = 400.0f;
const float DefaultSpeed  = 200.0f;
const float DefaultDistance = 500.0f;
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

	GetMesh()->SetAnimInstanceClass(UserDataAsset->AnimInstance);

	SetControlMode();
	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("AstroCharacter"));
	//PlayerType = EPlayerType::PLAYER_NONE;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AAstroCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	AstroHUD = GetWorld()->GetFirstPlayerController()->GetHUD();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("%s : I'm Server"), *GetName());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("%s : I'm Client"), *GetName());
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
	PEI->BindAction(InputActions->InputUpDown, ETriggerEvent::Triggered, this, &AAstroCharacter::UpDown);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AAstroCharacter::LookUp);
	PEI->BindAction(InputActions->InputTurn, ETriggerEvent::Triggered, this, &AAstroCharacter::Turn);
	PEI->BindAction(InputActions->InputExplore, ETriggerEvent::Triggered, this, &AAstroCharacter::Exploring);
	PEI->BindAction(InputActions->InputExplore, ETriggerEvent::Completed, this, &AAstroCharacter::UnExploring);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Triggered, this, &AAstroCharacter::Swift);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Completed, this, &AAstroCharacter::StopSwift);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Triggered, this, &AAstroCharacter::Jumping);
	PEI->BindAction(InputActions->InputLeftRight, ETriggerEvent::Triggered, this, &AAstroCharacter::LeftRight);
	PEI->BindAction(InputActions->InputSearch, ETriggerEvent::Triggered, this, &AAstroCharacter::Search);
	PEI->BindAction(InputActions->InputSearch, ETriggerEvent::Completed, this, &AAstroCharacter::UnSearch);
	PEI->BindAction(InputActions->ItemUse, ETriggerEvent::Triggered, this, &AAstroCharacter::ActiveItemWidget);
}


void AAstroCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

#pragma region For Control

void AAstroCharacter::UpDown(const FInputActionValue& Value)
{
	float NewAxisValue = Value.Get<float>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	if (CharacterStat->bSearch) return;
	AddMovementInput(ForwardDirection, NewAxisValue);

}

void AAstroCharacter::LeftRight(const FInputActionValue& Value)
{
	float NewAxisValue = Value.Get<float>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (CharacterStat->bSearch) return;
	AddMovementInput(RightDirection, NewAxisValue);
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
	if (!HasAuthority()) {
		UE_LOG(LogTemp, Log, TEXT("Speed : %f"), MovementSpeed);
	}
}
void AAstroCharacter::StopSwift(const FInputActionValue& Value)
{
	Server_Swift(DefaultSpeed);
	if (!HasAuthority()) {
		UE_LOG(LogTemp, Log, TEXT("Speed : %f"), MovementSpeed);
	}
}


void AAstroCharacter::Search(const FInputActionValue& Value) {
	auto NearInteract = Cast<IInteractObjInterface>(GetNearestObject());
	if (nullptr != NearInteract) {
		NearInteract->OnActivating();
		CharacterStat->bSearch = true;
	}
}

void AAstroCharacter::UnSearch(const FInputActionValue& Value)
{
	auto NearInteract = Cast<IInteractObjInterface>(GetNearestObject());
	if (nullptr != NearInteract) {
		NearInteract->StopActivating();
	}
	CharacterStat->bSearch = false;
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


void AAstroCharacter::Jumping(const FInputActionValue& Value)
{	
	Super::Jump();
	ExploreWidgetVisibleSet(false);
}


#pragma endregion

#pragma region Mission

//void AAstroCharacter::Req_MissionClear_Implementation(FName ObjectName)
//{
//	auto GameState = CastChecked<IAstroMissionManager>(GetWorld()->GetGameState());
//	if (GameState == nullptr)
//	{
//		UE_LOG(LogTemp, Log, TEXT("NULL GAMEMODE"));
//		return;
//	}
//
//	GameState->Resp_MissionClear(PlayerType, ObjectName);
//}

void AAstroCharacter::Req_MissionClear(FName ObjectName)
{
	MissionComponent->ClearCheck(ObjectName);
}

EPlayerType AAstroCharacter::ReturnTag()
{
	return MissionComponent->GetPlayerType();
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

UObject* AAstroCharacter::GetNearestObject()
{
	double MinDist = INT32_MAX;
	UObject* RetObj = nullptr;
	for (auto Hit : HitObj) {
		if (nullptr != Hit) {
			if (MinDist > FVector::Distance(GetActorLocation(), Hit->GetActorLocation())) {
				RetObj = Hit;
			}
		}
	}
	return RetObj;

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
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	
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


void AAstroCharacter::SearchObjectHit(AActor* Obj, bool bInAndOut)
{
	if (bInAndOut) {
		HitObj.Emplace(Obj);
	}
	else {
		if (HitObj.Contains(Obj)) {
			HitObj.Remove(Obj);
		}
	}
}

void AAstroCharacter::ExploreWidgetVisibleSet(bool InVisible) 
{
	UFunction* Function = AstroHUD->GetClass()->FindFunctionByName("SetVisibleUserStatus");
	if (Function) 
	{
		CharacterStat->SetExploring(InVisible);
		AstroHUD->ProcessEvent(Function, &CharacterStat->GetExplore());
	}
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
