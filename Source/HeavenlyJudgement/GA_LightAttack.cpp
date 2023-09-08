// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_LightAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "HJAbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

void UGA_LightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, LightAttackMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->OnCancelled.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->OnInterrupted.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->OnCompleted.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* UpdateNextComboEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboChangeTag, nullptr, false, false);
	if (UpdateNextComboEvent)
	{
		UpdateNextComboEvent->EventReceived.AddDynamic(this, &UGA_LightAttack::UpdateComboName);
		UpdateNextComboEvent->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* NextAttackEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, NextAttackTag, nullptr, false, false);
	if (NextAttackEvent)
	{
		NextAttackEvent->EventReceived.AddDynamic(this, &UGA_LightAttack::MoveNextAttack);
		NextAttackEvent->ReadyForActivation();
	}
}

void UGA_LightAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_LightAttack::MontageFinished()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_LightAttack::UpdateComboName(FGameplayEventData Payload)
{
	NextComboSectionName = UHJAbilitySystemBlueprintLibrary::GetRandomNameFromTagContainer(Payload.TargetTags);
	UE_LOG(LogTemp, Warning, TEXT("Next combo name is: %s"), *NextComboSectionName.ToString());
}

void UGA_LightAttack::MoveNextAttack(FGameplayEventData Payload)
{
	if (NextComboSectionName == NAME_None)
		return;

	USkeletalMeshComponent* mesh = GetOwningComponentFromActorInfo();
	if (mesh)
	{
		UAnimInstance* AnimBP = mesh->GetAnimInstance();
		if (AnimBP->Montage_GetCurrentSection() == NextComboSectionName)
		{
			return;
		}

		if (AnimBP && AnimBP->GetCurrentActiveMontage())
		{
			//RotateTowardsInput();
			AnimBP->Montage_SetNextSection(AnimBP->Montage_GetCurrentSection(), NextComboSectionName, AnimBP->GetCurrentActiveMontage());
			AnimBP->Montage_JumpToSection(NextComboSectionName, AnimBP->GetCurrentActiveMontage());
		}
	}
}
