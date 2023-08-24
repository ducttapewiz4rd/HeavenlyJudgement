// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HJGameplayAbilityTypes.h"
#include "GameplayEffectTypes.h"
#include "GameplayAbilitySpec.h"
#include "BaseCharacter.generated.h"

UCLASS()
class HEAVENLYJUDGEMENT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameplayAbility")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level = -1);

	FGameplayAbilitySpec* GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID = -1, bool broadCast = true, int level = 0);

	virtual void SendJumpEventsToActorAbility();

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag LandEventTag;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> JumpAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> DoubleJumpAbilityClass;

	virtual void GiveUniqueAbilities();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UHJAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComp; }
	FORCEINLINE class UHJAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void ApplyInitialEffect();

private:
	UPROPERTY()
	UHJAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY()
	UHJAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TMap<EAbilityInputID, TSubclassOf<class UGameplayAbility>> InitialAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TArray <TSubclassOf<class UGameplayEffect>> InitialEffects;

	virtual void Landed(const FHitResult& Hit) override;



};
