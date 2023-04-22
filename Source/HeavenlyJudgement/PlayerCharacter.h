// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* MappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* AbilityAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void HandleAbilityInput(const FInputActionValue& InputActionValue);

private:

	void SpawnWeapons();

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class ARevolver> RevolverClass;

	UPROPERTY()
	ARevolver* Revolver;
	
};
