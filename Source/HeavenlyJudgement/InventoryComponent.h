// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemSpec.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemChanged, FItemSpec*, bool);

class UBaseItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEAVENLYJUDGEMENT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GiveItem(const UBaseItem* itemCDO);

	FOnItemChanged onItemChanged;

private:
	UPROPERTY(VisibleAnywhere)
	TMap<int, FItemSpec> ItemContainer;

	UPROPERTY()
	class UAbilitySystemComponent* OwnerAbilitySystemComp;

	FActiveGameplayEffectHandle ApplyItemPassiveEffect(const UBaseItem* itemCDO) const;

	FActiveGameplayEffectHandle ApplyGameplayEffectToOwner(TSubclassOf<class UGameplayEffect> effectToApply) const;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<class ASword> SwordClass;
	UPROPERTY()
	ASword* Sword;

	void SpawnWeapons();
};
