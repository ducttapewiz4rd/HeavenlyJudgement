// Fill out your copyright notice in the Description page of Project Settings.


#include "Revolver.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"

void ARevolver::GunTrace()
{

	const FVector TraceStart = GetWeaponMesh()->GetSocketLocation(PistolMuzzleLocationSocketName);
	const FVector TraceDir = GetWeaponMesh()->GetSocketRotation(PistolMuzzleLocationSocketName).Vector();

	(GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceStart + TraceDir * 10000, ECC_Visibility));

	if (HitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *HitResult.GetActor()->GetName());
		DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Green, false, 1.f, 0, 1);

		FGameplayEventData eventData;

		FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor());
		eventData.TargetData = TargetData;
		eventData.ContextHandle = UAbilitySystemGlobals::Get().AllocGameplayEffectContext();
		eventData.ContextHandle.AddHitResult(HitResult);
		eventData.ContextHandle.AddInstigator(GetOwner(), this);

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), HitEventTag, eventData);
	}
	else
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceStart + TraceDir * 10000, FColor::Red, false, 1.f, 0, 1);
	}
		
		
	

	
}

