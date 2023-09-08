// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class HEAVENLYJUDGEMENT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
	FName GetWeaponSocketName() const { return WeaponSocketName; }
	UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	void AttachToOwner(USkeletalMeshComponent* OwnerMesh);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "BaseWeapon")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "BaseWeapon")
	FName WeaponSocketName;

};
