// Fill out your copyright notice in the Description page of Project Settings.


#include "Revolver.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"

void ARevolver::GunTrace()
{

	const FVector TraceStart = GetWeaponMesh()->GetSocketLocation(PistolMuzzleLocationSocketName);
	const FVector TraceDir = GetWeaponMesh()->GetSocketRotation(PistolMuzzleLocationSocketName).Vector();


	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceStart + TraceDir * 10000, ECC_Visibility);


	

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

void ARevolver::GunTraceTarget(AActor* PotentialTarget)
{

	const FVector TraceStart = GetWeaponMesh()->GetSocketLocation(PistolMuzzleLocationSocketName);
	const FVector TraceEnd = PotentialTarget ? PotentialTarget->GetActorLocation() : TraceStart + GetOwner()->GetActorForwardVector() * 10000;

	if (PotentialTarget)
	{
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

		if (HitResult.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *HitResult.GetActor()->GetName());
			FGameplayEventData eventData;

			FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor());
			eventData.TargetData = TargetData;
			eventData.ContextHandle = UAbilitySystemGlobals::Get().AllocGameplayEffectContext();
			eventData.ContextHandle.AddHitResult(HitResult);
			eventData.ContextHandle.AddInstigator(GetOwner(), this);

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), HitEventTag, eventData);

		}
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 2.0f, 0, 2.0f);
	}



}
