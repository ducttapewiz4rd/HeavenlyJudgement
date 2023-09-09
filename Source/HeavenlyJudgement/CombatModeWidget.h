// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UCombatModeWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentCombatModeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftFaceAbilityText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TopFaceAbilityText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightFaceAbilityText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BottomFaceAbilityText;

public:
	void UpdateCombatModeWidget(FText CurrentMode, FText Left, FText Top, FText Right);

	void ToggleCombatMode(FText CurrentMode);

	void SetDefaults();

	
};
