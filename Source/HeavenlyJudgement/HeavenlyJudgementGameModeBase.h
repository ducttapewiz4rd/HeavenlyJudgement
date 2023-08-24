// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HeavenlyJudgementGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API AHeavenlyJudgementGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void AddChest(class AChest* ChestToAdd);


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<AChest*> ChestsInLevel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBaseItem> Key;

	void SelectRandomChestToGiveKey();
	
};
