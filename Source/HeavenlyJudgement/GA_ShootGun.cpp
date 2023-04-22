// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ShootGun.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

void UGA_ShootGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* ShootMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, FiringMontage);


	if (ShootMontageTask)
	{
		ShootMontageTask->OnBlendOut.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
		ShootMontageTask->OnCancelled.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
		ShootMontageTask->OnInterrupted.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
		ShootMontageTask->OnCompleted.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
		ShootMontageTask->ReadyForActivation();
	}
}

void UGA_ShootGun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
