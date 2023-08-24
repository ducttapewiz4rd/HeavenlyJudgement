// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"
#include "PlayerCharacter.h"

void AGate::InteractWith(APlayerCharacter* player)
{
	Super::InteractWith(player);
	if (player->PlayerHasKey())
	{
		UE_LOG(LogTemp, Warning, TEXT("open sesame"));
	}
	
}
