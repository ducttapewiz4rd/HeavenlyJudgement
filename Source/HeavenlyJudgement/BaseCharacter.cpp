// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HJAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HJAttributeSet.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UHJAbilitySystemComponent>("AbilitySystemComp");
	AttributeSet = CreateDefaultSubobject<UHJAttributeSet>("AttributeSet");

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	ApplyInitialEffect();
	for (auto& Ability : InitialAbilities)
	{
		GiveAbility(Ability.Value, static_cast<int32>(Ability.Key));
	}


	if (AbilitySystemComp)
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
		AbilitySystemComp->GenericConfirmInputID = static_cast<int32>(EAbilityInputID::Confirm);
		AbilitySystemComp->GenericCancelInputID = static_cast<int32>(EAbilityInputID::Cancel);

	}
	
}

void ABaseCharacter::ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level)
{
	FGameplayEffectSpecHandle Spec = AbilitySystemComp->MakeOutgoingSpec(effectToApply, level, AbilitySystemComp->MakeEffectContext());
	AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*Spec.Data);
}

FGameplayAbilitySpec* ABaseCharacter::GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID, bool broadCast, int level)
{
	FGameplayAbilitySpecHandle specHandle = AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(newAbility, -1, inputID));

	FGameplayAbilitySpec* spec = AbilitySystemComp->FindAbilitySpecFromHandle(specHandle);
	return spec;
}
void ABaseCharacter::GiveUniqueAbilities()
{
	GiveAbility(JumpAbilityClass);
}

void ABaseCharacter::SendJumpEventsToActorAbility()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(JumpAbilityClass, true);
	}
	else
	{
		if (DoubleJumpAbilityClass)
		{
			GetAbilitySystemComponent()->TryActivateAbilityByClass(DoubleJumpAbilityClass, true);

		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::ApplyInitialEffect()
{
	if (InitialEffects.Num() > 0)
	{
		for (auto& effect : InitialEffects)
		{
			ApplyEffectToSelf(effect);
		}
	}
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, LandEventTag, FGameplayEventData());
}

