// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Gate.generated.h"

/**
 * 
 */
UCLASS()
class HEAVENLYJUDGEMENT_API AGate : public AInteractableActor
{
	GENERATED_BODY()

private:

	virtual void InteractWith(APlayerCharacter* player) override;
	
};
