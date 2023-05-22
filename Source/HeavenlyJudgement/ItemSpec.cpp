// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpec.h"
#include "GameplayEffect.h"
#include "BaseItem.h"

FItemSpec::FItemSpec(): ItemCDO{ nullptr }, PassiveEffectHandle{}, stackCount{ 0 }, handle{ INDEX_NONE }
{
}

FItemSpec::FItemSpec(const FItemSpec& rhs): 
ItemCDO{ rhs.ItemCDO },
PassiveEffectHandle{ rhs.PassiveEffectHandle },
stackCount{ rhs.stackCount },
handle{ rhs.handle },
onStackChanged{ rhs.onStackChanged }
{
}

FItemSpec::FItemSpec(const UBaseItem* item, FActiveGameplayEffectHandle handle): ItemCDO{ item }, PassiveEffectHandle{ handle }, stackCount{ 1 }, handle{ CreateNewHandle() }
{
}

bool FItemSpec::IsStackable() const
{
	return ItemCDO->IsStackable();
}

bool FItemSpec::IsConsumable() const
{
	return ItemCDO->IsConsumable();
}

void FItemSpec::PushStack()
{
	++stackCount;
	onStackChanged.Broadcast(stackCount);
}

bool FItemSpec::PopStack()
{
	--stackCount;
	onStackChanged.Broadcast(stackCount);
	return stackCount > 0;
}

const UGameplayEffect* FItemSpec::GetItemPassiveEffect() const
{
	auto passiveEffect = ItemCDO->GetPassiveGameplayEffect();

	if (passiveEffect)
	{
		return passiveEffect.GetDefaultObject();
	}
	return nullptr;
}

const TSubclassOf<class UGameplayAbility> FItemSpec::GetGrantedAbilityClass() const
{
	const UGameplayEffect* passiveEffectCDO = GetItemPassiveEffect();

	if (passiveEffectCDO && passiveEffectCDO->GrantedAbilities.Num() != 0)
	{
		return passiveEffectCDO->GrantedAbilities[0].Ability;
	}
	return TSubclassOf<UGameplayAbility>();
}

int FItemSpec::CreateNewHandle() const
{
	static int InventoryItemHandle = 0;
	return InventoryItemHandle++;
}
