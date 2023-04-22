// Fill out your copyright notice in the Description page of Project Settings.


#include "HJGameplayAbilityBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseCharacter.h"

void UHJGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AvatarCharacterBase = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());
}

bool UHJGameplayAbilityBase::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	if (Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		UHJGameplayAbilityBase* CDO = Cast<UHJGameplayAbilityBase>(GetClass()->GetDefaultObject());
		if (CDO)
		{
			CDO->onAbilityCommitted.Broadcast();
		}
		return true;
	}
	return false;
}
