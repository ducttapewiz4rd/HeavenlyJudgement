// Copyright Epic Games, Inc. All Rights Reserved.


#include "HeavenlyJudgementGameModeBase.h"
#include "Chest.h"

void AHeavenlyJudgementGameModeBase::AddChest(AChest* ChestToAdd)
{
	ChestsInLevel.AddUnique(ChestToAdd);
}

void AHeavenlyJudgementGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SelectRandomChestToGiveKey();
}

void AHeavenlyJudgementGameModeBase::SelectRandomChestToGiveKey()
{
	if (!ChestsInLevel.IsEmpty())
	{
		int randomNum = FMath::RandRange(0, ChestsInLevel.Num() - 1);
		UE_LOG(LogTemp, Warning, TEXT("%s would get the key added to its items"), *ChestsInLevel[randomNum]->GetName());
		AChest* TheChosenOne = ChestsInLevel[randomNum];
		TheChosenOne->SetContainedItem(Key);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Designer, there's no chests in the level to place the key! Bad!"));
	}
	
}
