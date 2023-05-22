// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "PlayerCharacter.h"
#include "HeavenlyJudgementGameModeBase.h"
#include "BaseItem.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

void AChest::SetContainedItem(TSubclassOf<class UBaseItem> Item)
{
	ContainedItem = Item;
}

void AChest::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AHeavenlyJudgementGameModeBase>(UGameplayStatics::GetGameMode(this));
	GiveSelfToGameMode();
}

void AChest::InteractWith(APlayerCharacter* Player)
{
	if (ContainedItem)
	{
		UInventoryComponent* InventoryComp = Player->GetInventoryComponent();
		if (InventoryComp)
		{
			InventoryComp->GiveItem(ContainedItem.GetDefaultObject());
		}
	}
}

void AChest::GiveSelfToGameMode()
{
	if (GameMode)
	{
		GameMode->AddChest(this);
	}
}
