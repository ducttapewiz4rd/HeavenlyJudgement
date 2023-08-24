// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Jump.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseCharacter.h"

void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_WaitGameplayEvent* WaitJumpEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LandEventTag, nullptr, false, false);
	if (WaitJumpEvent)
	{
		WaitJumpEvent->EventReceived.AddDynamic(this, &UGA_Jump::CharacterLanded);
		WaitJumpEvent->ReadyForActivation();
	}
	ABaseCharacter* Chara = GetAvatarAsCharacter();
	Chara->Jump();
}

void UGA_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Jump::CharacterLanded(FGameplayEventData Payload)
{
	K2_EndAbility();
}
