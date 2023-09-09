// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UCombatModeWidget* CombatModeWidget;

public:
	void UpdateCombatModeVisuals(FText CurrentMode, FText Left, FText Top, FText Right);

	void ResetCombatWidgetDefaults();

	void ToggleCombatName(FText NewName);
	
};
