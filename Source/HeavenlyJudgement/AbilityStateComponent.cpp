// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStateComponent.h"

// Sets default values for this component's properties
UAbilityStateComponent::UAbilityStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAbilityStateComponent::SwitchCurrentCombatMode()
{
	if (CurrentCombatMode == ECombatModeState::Item)
	{
		CurrentCombatMode = ECombatModeState::Sword;
		OnToggleCurrentCombatName.Broadcast(GetAbilitiesForState().ModeName);
		return;
	}

	int32 NextState = static_cast<int32>(CurrentCombatMode) + 1;
	CurrentCombatMode = static_cast<ECombatModeState>(NextState);
	OnToggleCurrentCombatName.Broadcast(GetAbilitiesForState().ModeName);
}


// Called when the game starts
void UAbilityStateComponent::BeginPlay()
{
	Super::BeginPlay();
	OnToggleCurrentCombatName.Broadcast(GetAbilitiesForState().ModeName);
	// ...
	
}


// Called every frame
void UAbilityStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FAbilityStruct UAbilityStateComponent::GetAbilitiesForState()
{
	if (StateToAbilityIndexMap.Contains(CurrentCombatMode))
	{
		int32 AbilityIndex = StateToAbilityIndexMap[CurrentCombatMode];
		if (AbilityArray.IsValidIndex(AbilityIndex))
		{
			return AbilityArray[AbilityIndex];
		}
	}
	return FAbilityStruct();
}

void UAbilityStateComponent::UpdateCurrentAbilityWidget()
{
	OnUpdateCombatModeWidget.Broadcast(GetAbilitiesForState());
}

void UAbilityStateComponent::ResetWidgetDefaults()
{
	OnResetDefaults.Broadcast();
}

