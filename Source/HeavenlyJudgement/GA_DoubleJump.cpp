// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_DoubleJump.h"
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

void UGA_DoubleJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* JumpMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, JumpingMontage);

	if (JumpMontageTask)
	{
		JumpMontageTask->ReadyForActivation();
	}

	ABaseCharacter* Chara = GetAvatarAsCharacter();
	UCharacterMovementComponent* MovementComponent = Chara->GetCharacterMovement();

	if (MovementComponent->IsFalling()) {
		FVector NewVelocity = Chara->GetVelocity();
		NewVelocity.Z = FMath::Max(NewVelocity.Z, 0.0f);
		Chara->GetCharacterMovement()->Velocity = NewVelocity;
	}
	MovementComponent->AddImpulse(GetAvatarActorFromActorInfo()->GetActorUpVector() * JumpForce, true);

	UAbilityTask_WaitGameplayEvent* WaitJumpEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LandEventTag, nullptr, false, false);
	if (WaitJumpEvent)
	{
		WaitJumpEvent->EventReceived.AddDynamic(this, &UGA_DoubleJump::CharacterLanded);
		WaitJumpEvent->ReadyForActivation();
	}

}

void UGA_DoubleJump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_DoubleJump::CharacterLanded(FGameplayEventData Payload)
{
	K2_EndAbility();
}
