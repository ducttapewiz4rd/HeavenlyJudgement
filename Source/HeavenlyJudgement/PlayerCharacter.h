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

	class UAbilityStateComponent* GetAbilityStateComponent() const { return AbilityStateComponent; }

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	bool IsLockedOn(AActor*& LockedOnActor);

	class UInventoryComponent* GetInventoryComponent() const { return InventoryComp; }

	void SetPlayerHasKey(bool HasKey);

	bool PlayerHasKey() const { return bHasKey; }

	

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
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ReadyAbilityAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LeftFaceAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void HandleAbilityInput(const FInputActionValue& InputActionValue);
	void LockOn();
	void LockOnToggle(const FInputActionValue& Value);
	void Interact();
	void ReadyAbility();
	void ReadyAbilityReleased();
	void LeftFaceActionPressed();


private:

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> LightAttackAbility;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag NextAttackTag;


	void SpawnWeapons();
	virtual void GiveUniqueAbilities() override;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class UInventoryComponent* InventoryComp;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere)
	AActor* LockedOnTarget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALockOnCapturer> LockOnCapturerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AInteractSphere> InteractSphereClass;

	UPROPERTY(EditDefaultsOnly)
	float LockOnRange = 2500.f;

	AActor* GetClosestTarget(TArray<AActor*> Targets, float& Distance);
	UPROPERTY()
	class AHJPlayerController* PlayerCont;

	bool bHasKey = false;

	UPROPERTY(EditDefaultsOnly)
	UAbilityStateComponent* AbilityStateComponent;

	UPROPERTY(VisibleAnywhere)
	bool bPressingAbilityReadyInput = false;


	
};
