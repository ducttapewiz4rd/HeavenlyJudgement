// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ToggleCombatMode.h"
#include "PlayerCharacter.h"

void UGA_ToggleCombatMode::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	APlayerCharacter* Chara = Cast<APlayerCharacter>(GetAvatarAsCharacter());
	Chara->SwitchCurrentCombatMode();
	K2_EndAbility();

}

void UGA_ToggleCombatMode::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
