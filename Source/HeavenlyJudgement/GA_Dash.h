
#pragma once

#include "CoreMinimal.h"
#include "HJGameplayAbilityBase.h"
#include "GA_Dash.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UGA_Dash : public UHJGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	UAnimMontage* DashMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	class UNiagaraSystem* DashFX;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float StopMovementTime = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float UpwardLiftDebuffer = 32.f;

	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float DashForce = 1000.f;

	FTimerHandle StopMovementTimerHandle;

	void StopMovement();
	
};
