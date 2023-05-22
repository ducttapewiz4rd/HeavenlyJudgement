// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseItem.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API UBaseItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE UTexture2D* GetIconTexture() const { return iconTexture; }
	FORCEINLINE FText GetDescription() const { return description; }
	FORCEINLINE FText GetItemName() const { return name; }
	//FORCEINLINE TSubclassOf<class UItemToolTip> GetToolTipClass() const { return toolTipClass; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetPassiveGameplayEffect() const { return EquipPassiveEffect; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetActiveGameplayEffect() const { return ActivationEffect; }
	FORCEINLINE bool IsStackable() const { return bIsStackable; }
	FORCEINLINE bool IsConsumable() const { return bIsConsumable; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FPrimaryAssetType AssetType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UTexture2D* iconTexture;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FText name;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FText description;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<UGameplayEffect> EquipPassiveEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<UGameplayEffect> ActivationEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	bool bIsStackable;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	bool bIsConsumable;
	//UPROPERTY(EditDefaultsOnly, Category = "Item")
	//TSubclassOf<UItemToolTip> toolTipClass;
	
};
