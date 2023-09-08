// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_LightAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "HJAbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "BaseCharacter.h"

void UGA_LightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	RotateTowardsInput();
	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, LightAttackMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->OnCancelled.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->OnInterrupted.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->OnCompleted.AddDynamic(this, &UGA_LightAttack::MontageFinished);
		MontagePlay->ReadyForActivation();
	}

	ACharacter* AvatarAsCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MovementComp = AvatarAsCharacter->GetCharacterMovement();
	OriginalWalkSpeed = MovementComp->MaxWalkSpeed;
	OriginalRotationRate = MovementComp->RotationRate;
	MovementComp->MaxWalkSpeed = 0.f;
	MovementComp->RotationRate = FRotator::ZeroRotator;

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

	UAbilityTask_WaitGameplayEvent* PushEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PushCharacterForwardTag, nullptr, false, false);
	if (PushEvent)
	{
		PushEvent->EventReceived.AddDynamic(this, &UGA_LightAttack::PushCharacter);
		PushEvent->ReadyForActivation();
	}
}

void UGA_LightAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ACharacter* AvatarAsCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MovementComp = AvatarAsCharacter->GetCharacterMovement();
	MovementComp->MaxWalkSpeed = OriginalWalkSpeed;
	MovementComp->RotationRate = OriginalRotationRate;
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
			RotateTowardsInput();
			AnimBP->Montage_SetNextSection(AnimBP->Montage_GetCurrentSection(), NextComboSectionName, AnimBP->GetCurrentActiveMontage());
			AnimBP->Montage_JumpToSection(NextComboSectionName, AnimBP->GetCurrentActiveMontage());
		}
	}
}

void UGA_LightAttack::PushCharacter(FGameplayEventData Payload)
{
	ACharacter* AvatarAsCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = AvatarAsCharacter->GetCharacterMovement();

	OriginalGroundFriction = MoveComp->GroundFriction;
	FVector PushDirection = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	FRotator PushRotation = FRotator(0, PushDirection.Rotation().Yaw, 0);
	MoveComp->GroundFriction = 0;
	FVector EvadeVelocity = PushDirection.GetSafeNormal() * CharacterForwardForce  * Payload.EventMagnitude;
	MoveComp->Velocity = EvadeVelocity;
	AvatarAsCharacter->SetActorRotation(PushRotation);

}

void UGA_LightAttack::RotateTowardsInput()
{
	ACharacter* AvatarAsCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MovementComp = AvatarAsCharacter->GetCharacterMovement();

	FVector RotateDirection;

	if (MovementComp->GetLastInputVector() == FVector::ZeroVector)
	{
		RotateDirection = AvatarAsCharacter->GetActorForwardVector();
	}
	else
	{
		RotateDirection = MovementComp->GetLastInputVector();
	}
	FRotator RotateRotation = FRotator(0, RotateDirection.Rotation().Yaw, 0);
	AvatarAsCharacter->SetActorRotation(RotateRotation);
}
