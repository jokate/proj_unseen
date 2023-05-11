// Fill out your copyright notice in the Description page of Project Settings.


#include "AstralBox.h"
#include "AstralBoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameStateBase.h"
#include "UI/AstroInteractionObj/AstralBoxWidget.h"

//Interface Header
#include "Interface/AstroCharacterInterface.h"

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
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	BoxStat = CreateDefaultSubobject<UAstralBoxComponent>(TEXT("BOXSTATUS"));	
	ActivationWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ACTIVATION"));
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
	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, [&]() {
		if (BoxStat->Percentage < 1.0f) {
			ActivationSetting(0.05f);
		}
		else {
			SetObjActiveComplete();
			GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
			
		}
	}, 0.05f, true);
}

void AAstralBox::StopActivating()
{
	GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
	ActivationSetting(0.0f);
}

void AAstralBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("충둘하였음"));
	auto MissionClearInterface = CastChecked<IAstroMissionClearInterface>(OtherActor);

	if(OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && MissionClearInterface)
	{
		MissionClearInterface->OnObjectCollided(OnActiveCompleted, OnItemIsGiven);
	}

	auto CharacterInterface = CastChecked<IAstroCharacterInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy) {

		CharacterInterface->ReturnActivateObjectDelegate().BindUObject(this, &AAstralBox::OnActivating);
		CharacterInterface->ReturnDeactivateObjectDelegate().BindUObject(this, &AAstralBox::StopActivating);

		BoxStat->SetActable(true);
		VisibleSetting(true);
	}
}

void AAstralBox::OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == this) 
	{
		return;
	}

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

		VisibleSetting(false);
		ActivationSetting(0.0f);
	}
}

void AAstralBox::VisibleSetting(bool InBoolean)

{
	IWidgetInterface* WidgetVisibleAction = CastChecked<IWidgetInterface>(ActivationWidget->GetUserWidgetObject());
	OnVisible Visible;
	Visible.BindLambda([&]() 
	{
		return BoxStat->SetActable(InBoolean);
	});

	WidgetVisibleAction->VisibilitySet(Visible);
}

void AAstralBox::ActivationSetting(float Percentage)
{
	IInteractionWidgetInterface* WidgetVisibleAction = CastChecked<IInteractionWidgetInterface>(ActivationWidget->GetUserWidgetObject());
	OnActivate Activate;
	Activate.BindLambda([&]() 
	{
		return BoxStat->SettingPercent(Percentage);
	});

	WidgetVisibleAction->PercentSet(Activate);
}
