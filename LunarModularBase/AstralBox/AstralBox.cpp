// Fill out your copyright notice in the Description page of Project Settings.


#include "AstralBox/AstralBox.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameStateBase.h"

#include "AccessControl/AccessControlComponent.h"
//Interface Header
#include "Interface/AstroCharacterInterface.h"
#include "Interface/InteractionWidgetInterface.h"
//Data Asset
#include "InteractionObjDataAsset.h"

// Sets default values
AAstralBox::AAstralBox()
{
	TObjectPtr<UInteractionObjDataAsset> DataAsset = nullptr;

	static ConstructorHelpers::FObjectFinder<UInteractionObjDataAsset> BOX_DATA(TEXT("/Script/LunarModularBase.InteractionObjDataAsset'/Game/DataAsset/AstralBoxDataAsset.AstralBoxDataAsset'"));
	if (BOX_DATA.Succeeded()) {
		DataAsset = BOX_DATA.Object;
	}

	check(DataAsset != nullptr);

	PrimaryActorTick.bCanEverTick = false;
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	ActivationWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ACTIVATION"));
	AccessChecker = CreateDefaultSubobject<UAccessControlComponent>(TEXT("ACCESSCHECKER"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));

	RootComponent = Box;

	Trigger->SetupAttachment(Box);
	Trigger->SetSphereRadius(DataAsset->SphereRadius);
	Trigger->SetCollisionProfileName(TEXT("CollisionDetector"));

	ActivationWidget->SetupAttachment(Box);
	ActivationWidget->SetRelativeLocation(DataAsset->RelativeLocation);
	ActivationWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ActivationWidget->SetWidgetClass(DataAsset->BoxCountWidget->GetClass());
	ActivationWidget->SetDrawSize(DataAsset->InteracionDrawSize);

	Box->SetStaticMesh(DataAsset->MeshData);
	Box->SetRelativeLocation(FVector(0.0f, -3.5f, 0.0f));
	ObjectID = DataAsset->ObjectID;
}


// Called when the game starts or when spawned
void AAstralBox::BeginPlay()
{
	Super::BeginPlay();

	IInteractionWidgetInterface* ActivationWidgetObject = CastChecked<IInteractionWidgetInterface>(ActivationWidget->GetUserWidgetObject());
	ActivationWidgetObject->ActivatedEventBind().BindUObject(this, &AAstralBox::SetObjActiveComplete);
}

void AAstralBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAstralBox::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AAstralBox::OnCharacterOverlapOut);
}

void AAstralBox::SetObjActiveComplete()
{
	OnItemIsGiven.ExecuteIfBound(ObjectItemData);
	OnActiveCompleted.ExecuteIfBound(ObjectID);
	SetActorEnableCollision(false);
}

void AAstralBox::OnActivating()
{
	IInteractionWidgetInterface* ActivationWidgetObject = CastChecked<IInteractionWidgetInterface>(ActivationWidget->GetUserWidgetObject());
	ActivationWidgetObject->OnActivateButtonPressed();
}

void AAstralBox::StopActivating()
{
	IInteractionWidgetInterface* ActivationWidgetObject = CastChecked<IInteractionWidgetInterface>(ActivationWidget->GetUserWidgetObject());
	ActivationWidgetObject->OnActivateButtonReleased();
}

void AAstralBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!AccessChecker->CanBeActivated(OtherActor))
		return;

	auto MissionClearInterface = CastChecked<IAstroMissionClearInterface>(OtherActor);

	if(OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		MissionClearInterface->OnObjectCollided(OnActiveCompleted, OnItemIsGiven);
	}

	auto CharacterInterface = CastChecked<IAstroCharacterInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy) {
		CharacterInterface->ReturnActivateObjectDelegate().BindUObject(this, &AAstralBox::OnActivating);
		CharacterInterface->ReturnDeactivateObjectDelegate().BindUObject(this, &AAstralBox::StopActivating);

		IInteractionWidgetInterface* ActivationWidgetObject = CastChecked<IInteractionWidgetInterface>(ActivationWidget->GetUserWidgetObject());
		ActivationWidgetObject->OnPlayerTriggered(true);
	}
}

void AAstralBox::OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this || !AccessChecker->CanBeActivated(OtherActor))
		return;

	auto MissionClearInterface = CastChecked<IAstroMissionClearInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		OnItemIsGiven.Unbind();
		OnActiveCompleted.Unbind();
	}

	auto CharacterInterface = Cast<IAstroCharacterInterface>(OtherActor);

	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && CharacterInterface) {

		CharacterInterface->ReturnActivateObjectDelegate().Unbind();
		CharacterInterface->ReturnDeactivateObjectDelegate().Unbind();

		IInteractionWidgetInterface* ActivationWidgetObject = CastChecked<IInteractionWidgetInterface>(ActivationWidget->GetUserWidgetObject());
		ActivationWidgetObject->OnPlayerTriggered(false);
	}

}
