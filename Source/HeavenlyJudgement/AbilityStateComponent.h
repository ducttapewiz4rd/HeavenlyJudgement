// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityStateComponent.generated.h"


UENUM()
enum ECombatModeState
{
	Sword UMETA(DisplayName = "Sword"),
	Gun UMETA(DisplayName = "Gun"),
	Magic UMETA(DisplayName = "Magic"),
	Item UMETA(DisplayName = "Item")
};

USTRUCT(BlueprintType)
struct FAbilityStruct
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = "Ability Struct")
	TSubclassOf<class UGameplayAbility> LeftFaceAbility;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Struct")
	TSubclassOf<class UGameplayAbility> TopFaceAbility;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Struct")
	TSubclassOf<class UGameplayAbility> RightFaceAbility;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Struct")
	FText ModeName;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Struct")
	FText LeftName;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Struct")
	FText TopName;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Struct")
	FText RightName;
	
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateCombatModeWidget, FAbilityStruct, CombatModeInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToggleCurrentCombatName, FText, Name);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetDefaults);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEAVENLYJUDGEMENT_API UAbilityStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityStateComponent();
	UPROPERTY(EditAnywhere, Category = "Combat Mode")
	TEnumAsByte<ECombatModeState> CurrentCombatMode;

	void SwitchCurrentCombatMode();

	FOnUpdateCombatModeWidget OnUpdateCombatModeWidget;
	FOnToggleCurrentCombatName OnToggleCurrentCombatName;
	FOnResetDefaults OnResetDefaults;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities")
	TArray<FAbilityStruct> AbilityArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities")
	TMap<TEnumAsByte<ECombatModeState>, int32> StateToAbilityIndexMap;
	
	FAbilityStruct GetAbilitiesForState();

	void UpdateCurrentAbilityWidget();
	void ResetWidgetDefaults();

};
