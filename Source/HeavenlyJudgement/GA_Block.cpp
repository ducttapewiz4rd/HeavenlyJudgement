// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Block.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "HJAbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UGA_Block::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* BlockMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, BlockMontage);
	GetAvatarAsCharacter()->GetCharacterMovement()->StopMovementImmediately();
	//APlayerController* PC = GetAvatarAsCharacter()->GetController<APlayerController>();
	//GetAvatarAsCharacter()->DisableInput(PC);
	if (BlockMontageTask)
	{
		BlockMontageTask->OnBlendOut.AddDynamic(this, &UGA_Block::K2_EndAbility);
		BlockMontageTask->OnCancelled.AddDynamic(this, &UGA_Block::K2_EndAbility);
		BlockMontageTask->OnInterrupted.AddDynamic(this, &UGA_Block::K2_EndAbility);
		BlockMontageTask->OnCompleted.AddDynamic(this, &UGA_Block::K2_EndAbility);
		BlockMontageTask->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* EnableStatusEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EnableBlockingStatusTag, nullptr, false, false);
	if (EnableStatusEvent)
	{
		EnableStatusEvent->EventReceived.AddDynamic(this, &UGA_Block::EnableBlockStatus);
		EnableStatusEvent->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* DisableStatusEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, DisableBlockingStatusTag, nullptr, false, false);
	if (DisableStatusEvent)
	{
		DisableStatusEvent->EventReceived.AddDynamic(this, &UGA_Block::DisableBlockStatus);
		DisableStatusEvent->ReadyForActivation();
	}
	UAbilityTask_WaitGameplayEvent* BlockEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, BlockEventTag, nullptr, false, false);
	if (BlockEvent)
	{
		BlockEvent->EventReceived.AddDynamic(this, &UGA_Block::PlayerIsBlocking);
		BlockEvent->ReadyForActivation();
	}

}

void UGA_Block::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	K2_ApplyGameplayEffectSpecToOwner(MakeOutgoingGameplayEffectSpec(RemoveBlockStatusEffect));
	APlayerController* PC = GetAvatarAsCharacter()->GetController<APlayerController>();
	GetAvatarAsCharacter()->EnableInput(PC);

}

void UGA_Block::EnableBlockStatus(FGameplayEventData Data)
{
	K2_ApplyGameplayEffectSpecToOwner(MakeOutgoingGameplayEffectSpec(BlockEffect));


}

void UGA_Block::DisableBlockStatus(FGameplayEventData Data)
{
	K2_ApplyGameplayEffectSpecToOwner(MakeOutgoingGameplayEffectSpec(RemoveBlockStatusEffect));

}

void UGA_Block::PlayerIsBlocking(FGameplayEventData Data)
{
	const AActor* BlockingChara = GetAvatarActorFromActorInfo();
	const AActor* AttackingChara = Data.Instigator.Get();
	FRotator BlockRotation = BlockingChara->GetActorRotation();
	FRotator AttackRotation = AttackingChara->GetActorRotation();
	float AngleCheck = BlockRotation.Yaw - AttackRotation.Yaw;
	if (AngleCheck > 150.f || AngleCheck < -150.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character block is valid."));
		UCharacterMovementComponent* MovComp = GetAvatarAsCharacter()->GetCharacterMovement();
		MovComp->AddImpulse(AttackingChara->GetActorForwardVector() * BlockForce, true);
	}
	else
	{
		//Activate a gameplay effect that deals 1.5x the amount of damage through a magnitude/tag
		//this is akin to "counter" damage you see in souls games.
		UE_LOG(LogTemp, Warning, TEXT("Character isn't turned towards the attacker enough. Block invalidated."));
	}
	

}
