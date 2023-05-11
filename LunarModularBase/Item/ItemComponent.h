// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemComponent.generated.h"

class UAstroItemData;
class UAstroActiveItemData;

DECLARE_DELEGATE_OneParam(FOnUseItemDelegate, class UAstroItemData* /*InItemData*/);
DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UAstroItemData* /*InItemData*/);

USTRUCT(BlueprintType)
struct FUseItemDelegateWrapper {
	GENERATED_BODY()

	FUseItemDelegateWrapper() {}
	FUseItemDelegateWrapper(const FOnUseItemDelegate& InItemDelegate) : ItemDeleagate(InItemDelegate) {}

	FOnUseItemDelegate ItemDeleagate;
};

USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper {
	GENERATED_BODY()

	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}

	FOnTakeItemDelegate ItemDelegate;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNARMODULARBASE_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Meta = (PrivateAccess = "true"))
	TArray<class UAstroItemData*> ItemContainer;
public:	
	void ItemWidgetActive();
protected :

	//Item Init
public :
	void InitItem(UAstroItemData* ItemData);

	//Item Use Events
public : 
	UPROPERTY()
	TMap<uint8, FUseItemDelegateWrapper> ItemUseEvents;

	void ItemUse(UAstroItemData* InItemData);

protected:

	void InstallItem(UAstroItemData* InItemData);

	void OperateItem(UAstroItemData* InItemData);

	//Request Server this Item is For mission
	UFUNCTION(Server, Reliable)
	void RequestMissionClearCheck(UAstroItemData* InItemData);
		
};
