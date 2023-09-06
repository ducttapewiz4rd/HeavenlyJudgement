// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HJGameplayAbilityBase.h"
#include "GA_ToggleCombatMode.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UGA_ToggleCombatMode : public UHJGameplayAbilityBase
{
	GENERATED_BODY()
private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
};
