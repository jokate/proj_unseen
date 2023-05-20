// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/AstroInteractableObject.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Interface/AstroCharacterInterface.h"
#include "GameFramework/GameStateBase.h"

#include "AccessControl/AccessControlComponent.h"
#include "InteractionObjDataAsset.h"

// Sets default values
AAstroInteractableObject::AAstroInteractableObject()
{
	TObjectPtr<UInteractionObjDataAsset> DataAsset = nullptr;

	static ConstructorHelpers::FObjectFinder<UInteractionObjDataAsset> BOX_DATA(TEXT("/Script/LunarModularBase.InteractionObjDataAsset'/Game/DataAsset/AstralBoxDataAsset.AstralBoxDataAsset'"));
	if (BOX_DATA.Succeeded()) {
		DataAsset = BOX_DATA.Object;
	}

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	ActivationWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ACTIVATION"));
	AccessChecker = CreateDefaultSubobject<UAccessControlComponent>(TEXT("ACCESSCHECKER"));
	ObjectTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("OBJECTTRIGGER"));


	check(DataAsset != nullptr);
	ObjectTrigger->SetupAttachment(Mesh);
	ObjectTrigger->SetSphereRadius(DataAsset->SphereRadius);
	ObjectTrigger->SetCollisionProfileName(TEXT("ObjectTrigger"));

	ActivationWidget->SetupAttachment(Mesh);
	ActivationWidget->SetRelativeLocation(DataAsset->RelativeLocation);
	ActivationWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ActivationWidget->SetWidgetClass(DataAsset->BoxCountWidget->GetClass());
	ActivationWidget->SetDrawSize(DataAsset->InteracionDrawSize);

	Mesh->SetStaticMesh(DataAsset->MeshData);
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, 0.0f));
	bReplicates = true;
}


// Called when the game starts or when spawned
void AAstroInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
	
}
void AAstroInteractableObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ObjectTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAstroInteractableObject::OnCharacterOverlap);
	ObjectTrigger->OnComponentEndOverlap.AddDynamic(this, &AAstroInteractableObject::OnCharacterOverlapOut);
}

void AAstroInteractableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AAstroInteractableObject::SetObjActiveComplete()
{
	K2_OnObjectActive();
	ObjectTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetPercentage(0.0f);
}

void AAstroInteractableObject::OnActivating()
{
	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, [&]() {
		SetPercentage(ActivationPercent + ActivateIncreasePercentage);
	}, ActivateIncreasePercentage, true);
}

void AAstroInteractableObject::StopActivating()
{
	GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
	SetPercentage(0.0f);
}

void AAstroInteractableObject::SetPercentage(float Infloat)
{
	ActivationPercent = Infloat;
	K2_OnActivateFunctionCall(ActivationPercent);

	if (ActivationPercent > ActivationFullPercent)
	{
		SetObjActiveComplete();
		GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
	}
}

void AAstroInteractableObject::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!AccessChecker->CanBeActivated(OtherActor))
		return;

	auto CharacterInterface = Cast<IAstroCharacterInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && CharacterInterface) 
	{
		CharacterInterface->ReturnActivateObjectDelegate().BindUObject(this, &AAstroInteractableObject::OnActivating);
		CharacterInterface->ReturnDeactivateObjectDelegate().BindUObject(this, &AAstroInteractableObject::StopActivating);
		K2_OnCharacterOverlapped();
	}
}

void AAstroInteractableObject::OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!AccessChecker->CanBeActivated(OtherActor))
		return;

	auto CharacterInterface = Cast<IAstroCharacterInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy &&  CharacterInterface)
	{
		CharacterInterface->ReturnActivateObjectDelegate().Unbind();
		CharacterInterface->ReturnDeactivateObjectDelegate().Unbind();
		if (ActivationPercent > ActivationFullPercent) 
		{
			CharacterInterface->ActivationComplete(this);
		}
		K2_OnCharacterOverlapOut();
	}
}