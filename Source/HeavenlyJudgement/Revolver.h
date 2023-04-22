// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "GameplayEffectTypes.h"
#include "Revolver.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API ARevolver : public ABaseWeapon
{
	GENERATED_BODY()

public:
	void GunTrace();
	
private:


UPROPERTY(EditDefaultsOnly, Category = "Revolver")
int CurrentAmmo;

UPROPERTY(EditDefaultsOnly, Category = "Revolver")
int AmmoCapacity = 5;

UPROPERTY(EditDefaultsOnly, Category = "Revolver")
int AmmoReserved = 10;

FHitResult HitResult;

UPROPERTY(EditDefaultsOnly, Category = "Revolver")
FName PistolMuzzleLocationSocketName {"RevolverMuzzle"};

UPROPERTY(EditDefaultsOnly, Category = "Revolver")
FGameplayTag HitEventTag;
	
};
