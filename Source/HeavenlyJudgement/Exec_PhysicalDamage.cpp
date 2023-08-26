// Fill out your copyright notice in the Description page of Project Settings.


#include "Exec_PhysicalDamage.h"
#include "HJAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

struct DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);




	DamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHJAttributeSet, Health, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHJAttributeSet, Attack, Source, true);

	}

};

static DamageCapture& GetDamageCapture()
{
	static DamageCapture DamageCaptureVar;
	return DamageCaptureVar;
}

UExec_PhysicalDamage::UExec_PhysicalDamage()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().HealthDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackDef);

}

void UExec_PhysicalDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	//out variables
	float OutHealth = 0.0f;

	//capture
	float HealthMagnitude = 0.0f;
	float AttackMagnitude = 0.0f;
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HealthDef, FAggregatorEvaluateParameters(), HealthMagnitude);
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackDef, FAggregatorEvaluateParameters(), AttackMagnitude);


	UAbilitySystemComponent* TargetAbilitySystem = ExecParams.GetTargetAbilitySystemComponent();
	if (TargetAbilitySystem)
	{
		FGameplayTag MyTagToCheck = FGameplayTag::RequestGameplayTag("Status.Blocking");
		bool bIsBlocking = TargetAbilitySystem->HasMatchingGameplayTag(MyTagToCheck);
		if (bIsBlocking)
		{
			FGameplayEventData EventData;
			EventData.Instigator = ExecParams.GetSourceAbilitySystemComponent()->GetOwner();
			TargetAbilitySystem->HandleGameplayEvent(EventTag, &EventData);
			//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ExecParams.GetTargetAbilitySystemComponent()->GetOwner(), EventTag, EventData);
			return;
		}
	}

	OutHealth = HealthMagnitude - AttackMagnitude;
	ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Override, OutHealth));
}
