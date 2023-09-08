// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ShootGun.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Revolver.h"
#include "PlayerCharacter.h"
#include "BaseCharacter.h"

void UGA_ShootGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//UAbilityTask_PlayMontageAndWait* ShootMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, FiringMontage);
	//Revolver = Cast<APlayerCharacter>(GetAvatarAsCharacter())->GetRevolver();
	//APlayerCharacter* Pam = Cast<APlayerCharacter>(GetAvatarAsCharacter());

	//if (ShootMontageTask)
	//{
	//	ShootMontageTask->OnBlendOut.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
	//	ShootMontageTask->OnCancelled.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
	//	ShootMontageTask->OnInterrupted.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
	//	ShootMontageTask->OnCompleted.AddDynamic(this, &UGA_ShootGun::K2_EndAbility);
	//	ShootMontageTask->ReadyForActivation();
	//}


	//UAbilityTask_WaitGameplayEvent* WaitHit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, HitEventTag, nullptr, false, false);
	//if (WaitHit)
	//{
	//	WaitHit->EventReceived.AddDynamic(this, &UGA_ShootGun::Hit);
	//	WaitHit->ReadyForActivation();
	//}

	//AActor* Target;
	//if (Pam->IsLockedOn(Target))
	//{
	//	if (Target)
	//	{
	//		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Pam->GetActorLocation(), Target->GetActorLocation());
	//		LookAtRot.Pitch = 0;
	//		Pam->SetActorRotation(LookAtRot);
	//		Revolver->GunTraceTarget(Target);

	//	}
	//}
	//else
	//{
	//	
	//	Revolver->GunTrace();
	//}

	


}

void UGA_ShootGun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_ShootGun::Hit(FGameplayEventData Payload)
{
	
	if (Payload.TargetData.Num() == 0) return;
	
	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Payload.TargetData, 0);
	for (AActor* TargetActor : TargetActors)
	{


	}
}
