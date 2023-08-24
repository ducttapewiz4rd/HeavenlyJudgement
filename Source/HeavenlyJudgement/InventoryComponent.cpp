// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "BaseItem.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerAbilitySystemComp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::GiveItem(const UBaseItem* itemCDO)
{
	for (auto& pair : ItemContainer)
	{
		if (pair.Value.GetItem() == itemCDO && pair.Value.IsStackable())
		{
			pair.Value.PushStack();
			return;
		}
	}


	FActiveGameplayEffectHandle handle = ApplyItemPassiveEffect(itemCDO);
	FItemSpec newItemSpec = FItemSpec(itemCDO, handle);
	onItemChanged.Broadcast(&ItemContainer.Add(newItemSpec.GetHandle(), newItemSpec), true);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *itemCDO->GetName());
}

FActiveGameplayEffectHandle UInventoryComponent::ApplyItemPassiveEffect(const UBaseItem* itemCDO) const
{
	TSubclassOf<UGameplayEffect> passiveEffect = itemCDO->GetPassiveGameplayEffect();
	return ApplyGameplayEffectToOwner(passiveEffect);
}

FActiveGameplayEffectHandle UInventoryComponent::ApplyGameplayEffectToOwner(TSubclassOf<class UGameplayEffect> effectToApply) const
{
	if (effectToApply)
	{
		FGameplayEffectSpecHandle spec = OwnerAbilitySystemComp->MakeOutgoingSpec(effectToApply, 1, 
			OwnerAbilitySystemComp->MakeEffectContext());
		return OwnerAbilitySystemComp->ApplyGameplayEffectSpecToSelf(*spec.Data);
	}
	return FActiveGameplayEffectHandle();
}

