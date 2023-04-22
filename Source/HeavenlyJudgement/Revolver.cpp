// Fill out your copyright notice in the Description page of Project Settings.


#include "Revolver.h"

void ARevolver::GunTrace()
{

	const FVector TraceStart = GetWeaponMesh()->GetSocketLocation(PistolMuzzleLocationSocketName);
	const FVector TraceDir = GetWeaponMesh()->GetSocketRotation(PistolMuzzleLocationSocketName).Vector();

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceStart + TraceDir * 10000, ECC_Visibility))
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: "), *HitResult.GetActor()->GetName());
		
	}
}

