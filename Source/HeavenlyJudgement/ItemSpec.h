// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "ItemSpec.generated.h"


/**
 * 
 */
class UBaseItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStackChanged, int, newStackCount);

USTRUCT(BlueprintType)
struct HEAVENLYJUDGEMENT_API FItemSpec
{
	GENERATED_BODY()

	FItemSpec();

	TArray <FActiveGameplayEffectHandle> GetActiveEffects() const { return PassiveEffectHandle; }

	//copy constructor
	FItemSpec(const FItemSpec& rhs);

	//custom constructor
	FItemSpec(const UBaseItem* item, FActiveGameplayEffectHandle handle);

	FORCEINLINE const UBaseItem* GetItem() const { return ItemCDO; }

	bool IsStackable() const;
	bool IsConsumable() const;
	void PushStack();
	bool PopStack();
	int GetStackCount() const { return stackCount; }

	FORCEINLINE bool IsValid() const { return handle != INDEX_NONE; }
	FORCEINLINE int GetHandle() const { return handle; }

	const class UGameplayEffect* GetItemPassiveEffect() const;
	const TSubclassOf<class UGameplayAbility> GetGrantedAbilityClass() const;

	FOnStackChanged onStackChanged;

private:
	const UBaseItem* ItemCDO;
	TArray <FActiveGameplayEffectHandle> PassiveEffectHandle;
	int stackCount = 1;
	int handle;

	int CreateNewHandle() const;
};
