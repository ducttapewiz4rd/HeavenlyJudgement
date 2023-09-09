// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HJPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API AHJPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* newPawn) override;

private:
	UPROPERTY()
	class APlayerCharacter* Pam;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInGameUI> InGameUIClass;

	UPROPERTY()
	UInGameUI* InGameUI;
	
	UFUNCTION()
	void UpdateCombatWidget(struct FAbilityStruct CombatTypeInfo);

	UFUNCTION()
	void ToggleModeName(FText Name);

	UFUNCTION()
	void ResetCombatWidget();
};
