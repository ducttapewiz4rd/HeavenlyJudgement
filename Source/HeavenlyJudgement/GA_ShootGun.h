// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HJGameplayAbilityBase.h"
#include "GA_ShootGun.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UGA_ShootGun : public UHJGameplayAbilityBase
{
	GENERATED_BODY()
private:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	void Hit(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Fire Gun")
	UAnimMontage* FiringMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Fire Gun")
	class ARevolver* Revolver;

	UPROPERTY(EditDefaultsOnly, Category = "Fire Gun")
	FGameplayTag HitEventTag;

	
};
