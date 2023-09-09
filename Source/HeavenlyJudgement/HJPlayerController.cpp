// Fill out your copyright notice in the Description page of Project Settings.


#include "HJPlayerController.h"
#include "PlayerCharacter.h"
#include "InGameUI.h"
#include "AbilityStateComponent.h"

void AHJPlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);
	Pam = Cast<APlayerCharacter>(newPawn);
	if (Pam && InGameUIClass)
	{
		InGameUI = CreateWidget<UInGameUI>(this, InGameUIClass);
		InGameUI->AddToViewport();
		InGameUI->ResetCombatWidgetDefaults();
		Pam->GetAbilityStateComponent()->OnUpdateCombatModeWidget.AddDynamic(this, &AHJPlayerController::UpdateCombatWidget);
		Pam->GetAbilityStateComponent()->OnToggleCurrentCombatName.AddDynamic(this, &AHJPlayerController::ToggleModeName);
		Pam->GetAbilityStateComponent()->OnResetDefaults.AddDynamic(this, &AHJPlayerController::ResetCombatWidget);

	}
}

void AHJPlayerController::UpdateCombatWidget(FAbilityStruct CombatTypeInfo)
{
	InGameUI->UpdateCombatModeVisuals(CombatTypeInfo.ModeName, CombatTypeInfo.LeftName, CombatTypeInfo.TopName, CombatTypeInfo.RightName);
}

void AHJPlayerController::ToggleModeName(FText Name)
{
	InGameUI->ToggleCombatName(Name);
}

void AHJPlayerController::ResetCombatWidget()
{
	InGameUI->ResetCombatWidgetDefaults();

}
