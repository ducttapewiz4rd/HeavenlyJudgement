// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatModeWidget.h"
#include "Components/TextBlock.h"

void UCombatModeWidget::UpdateCombatModeWidget(FText CurrentMode, FText Left, FText Top, FText Right)
{
	CurrentCombatModeText->SetText(CurrentMode);
	LeftFaceAbilityText->SetText(Left);
	TopFaceAbilityText->SetText(Top);
	RightFaceAbilityText->SetText(Right);
}

void UCombatModeWidget::ToggleCombatMode(FText CurrentMode)
{
	CurrentCombatModeText->SetText(CurrentMode);

}

void UCombatModeWidget::SetDefaults()
{
	LeftFaceAbilityText->SetText(FText::FromString("Light Attack"));
	TopFaceAbilityText->SetText(FText::FromString("Heavy Attack"));
	RightFaceAbilityText->SetText(FText::FromString(""));
	BottomFaceAbilityText->SetText(FText::FromString("Jump"));
}
