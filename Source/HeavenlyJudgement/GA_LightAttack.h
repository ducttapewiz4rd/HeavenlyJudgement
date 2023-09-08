// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HJGameplayAbilityBase.h"
#include "GA_LightAttack.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UGA_LightAttack : public UHJGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	class UAnimMontage* LightAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag ComboChangeTag;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag NextAttackTag;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag PushCharacterForwardTag;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float CharacterForwardForce;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void UpdateComboName(FGameplayEventData Payload);

	UFUNCTION()
	void MoveNextAttack(FGameplayEventData Payload);

	UFUNCTION()
	void PushCharacter(FGameplayEventData Payload);

	void RotateTowardsInput();

	float OriginalWalkSpeed;
	float OriginalGroundFriction;
	FRotator OriginalRotationRate;

	FName NextComboSectionName;
	
};
