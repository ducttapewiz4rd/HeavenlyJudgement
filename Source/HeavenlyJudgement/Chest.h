// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Chest.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API AChest : public AInteractableActor
{
	GENERATED_BODY()

public:
	void SetContainedItem(TSubclassOf<class UBaseItem> Item);

protected:
	virtual void BeginPlay() override;

	virtual void InteractWith(APlayerCharacter* Player) override;

private:
	virtual void GiveSelfToGameMode();

	UPROPERTY()
	class AHeavenlyJudgementGameModeBase* GameMode;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseItem> ContainedItem;

	
};
