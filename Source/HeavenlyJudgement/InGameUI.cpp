// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "CombatModeWidget.h"

void UInGameUI::UpdateCombatModeVisuals(FText CurrentMode, FText Left, FText Top, FText Right)
{
	CombatModeWidget->UpdateCombatModeWidget(CurrentMode, Left, Top, Right);
}

void UInGameUI::ResetCombatWidgetDefaults()
{
	CombatModeWidget->SetDefaults();
}

void UInGameUI::ToggleCombatName(FText NewName)
{
	CombatModeWidget->ToggleCombatMode(NewName);
}
