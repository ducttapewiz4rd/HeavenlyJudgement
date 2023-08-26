// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HJGameplayAbilityBase.h"
#include "GA_Block.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UGA_Block : public UHJGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
	UAnimMontage* BlockMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
	FGameplayTag EnableBlockingStatusTag;
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	FGameplayTag DisableBlockingStatusTag;
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	FGameplayTag BlockEventTag;

	UFUNCTION()
	void EnableBlockStatus(FGameplayEventData Data);

	UFUNCTION()
	void DisableBlockStatus(FGameplayEventData Data);

	UFUNCTION()
	void PlayerIsBlocking(FGameplayEventData Data);
};
