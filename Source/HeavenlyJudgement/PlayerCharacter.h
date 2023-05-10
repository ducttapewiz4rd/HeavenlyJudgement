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

	virtual void Tick(float DeltaTime) override;

	class ARevolver* GetRevolver() const { return Revolver; }

	bool IsLockedOn(AActor*& LockedOnActor);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* MappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* AbilityAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LockOnAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ToggleLockOnAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void HandleAbilityInput(const FInputActionValue& InputActionValue);
	void LockOn();
	void LockOnToggle(const FInputActionValue& Value);

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

	UPROPERTY(VisibleAnywhere)
	AActor* LockedOnTarget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALockOnCapturer> LockOnCapturerClass;

	UPROPERTY(EditDefaultsOnly)
	float LockOnRange = 2500.f;

	AActor* GetClosestTarget(TArray<AActor*> Targets, float& Distance);
	UPROPERTY()
	class AHJPlayerController* PlayerCont;


	
};
