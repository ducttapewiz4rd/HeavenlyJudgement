// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Dash.h"
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"


void UGA_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ABaseCharacter* Chara = GetAvatarAsCharacter();
	Chara->GetMesh()->SetHiddenInGame(true);
	UNiagaraFunctionLibrary::SpawnSystemAttached(DashFX, Chara->GetRootComponent(), NAME_None, Chara->GetActorLocation(), Chara->GetActorRotation(), EAttachLocation::KeepWorldPosition, true);
	//UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashFX, Chara->GetActorLocation(), Chara->GetActorRotation(), FVector(5.f, 5.f, 5.f));
	Chara->GetMesh()->GetAnimInstance()->Montage_Play(DashMontage);
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	FVector ImpulseDirection;
	if (MoveComp->GetLastInputVector() == FVector::ZeroVector)
	{
		ImpulseDirection = Chara->GetActorForwardVector();
	}
	else
	{
		ImpulseDirection = MoveComp->GetLastInputVector();
	}

	MoveComp->AddImpulse(ImpulseDirection * DashForce + (Chara->GetActorUpVector() * (DashForce/UpwardLiftDebuffer)), true);
	GetWorld()->GetTimerManager().SetTimer(StopMovementTimerHandle, this, &UGA_Dash::StopMovement, StopMovementTime, false);

}

void UGA_Dash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_Dash::StopMovement()
{
	ABaseCharacter* Chara = GetAvatarAsCharacter();
	Chara->GetMesh()->SetHiddenInGame(false);
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	MoveComp->StopMovementImmediately();
	K2_EndAbility();
}
