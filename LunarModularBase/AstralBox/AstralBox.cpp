// Fill out your copyright notice in the Description page of Project Settings.


#include "AstralBox.h"
#include "AstralBoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameStateBase.h"
#include "UI/AstroInteractionObj/AstralBoxWidget.h"
#include "Mission/AstroMissionSingleton.h"
//Interface Header
#include "Interface/AstroMissionManager.h"
#include "Interface/AstroCharacterInterface.h"
#include "Interface/AstroMissionClearInterface.h"

//Data Asset
#include "InteractionObjDataAsset.h"
#include "Net/UnrealNetwork.h"

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
	auto CastedPlayer = Cast<IAstroMissionClearInterface>(Player);
	if (CastedPlayer != nullptr) {
		CastedPlayer->Req_MissionClear(ObjectID);
	}
	SetActorEnableCollision(false);
}

void AAstralBox::OnActivating()
{
	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, [&]() {
		if (BoxStat->Percentage < 1.0f) {
			UE_LOG(LogTemp, Log, TEXT("%s : 작동 중.."), *GetActorNameOrLabel());
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
	UE_LOG(LogTemp, Log, TEXT("%s : 작동 중지"), *GetActorNameOrLabel());
	GetWorld()->GetTimerManager().ClearTimer(ActivationTimer);
	ActivationSetting(0.0f);
}

void AAstralBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AAstralBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("충둘하였음"));
	Player = OtherActor;
	auto Character = CastChecked<IAstroCharacterInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && Character) {
		Character->SearchObjectHit(this, true);
		BoxStat->SetActable(true);
		VisibleSetting(true);
	}
}

void AAstralBox::OnCharacterOverlapOut(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("충둘에서 나왔다"));
	Player = nullptr;
	auto Character = Cast<IAstroCharacterInterface>(OtherActor);
	if (OtherActor->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && Character) {
		Character->SearchObjectHit(this, false);
		VisibleSetting(false);
		ActivationSetting(0.0f);
	}
}

void AAstralBox::VisibleSetting(bool InBoolean)

{
	IWidgetInterface* WidgetVisibleAction = CastChecked<IWidgetInterface>(ActivationWidget->GetUserWidgetObject());
	OnVisible Visible;
	Visible.BindLambda([&]() {
		return BoxStat->SetActable(InBoolean);
	});

	WidgetVisibleAction->VisibilitySet(Visible);
}

void AAstralBox::ActivationSetting(float Percentage)
{
	IInteractionWidgetInterface* WidgetVisibleAction = CastChecked<IInteractionWidgetInterface>(ActivationWidget->GetUserWidgetObject());
	OnActivate Activate;
	Activate.BindLambda([&]() {
		return BoxStat->SettingPercent(Percentage);
		});

	WidgetVisibleAction->PercentSet(Activate);
}
