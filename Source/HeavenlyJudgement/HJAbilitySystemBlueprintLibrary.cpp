// Fill out your copyright notice in the Description page of Project Settings.


#include "HJAbilitySystemBlueprintLibrary.h"

FName UHJAbilitySystemBlueprintLibrary::GetTagNameLast(const FGameplayTag& Tag)
{
	FGameplayTag parentTag = Tag.RequestDirectParent();

	FString TagStr = Tag.ToString();
	FString ParentStr = parentTag.ToString() + ".";

	TagStr.RemoveAt(0, ParentStr.Len());
	return FName(TagStr);
}

FName UHJAbilitySystemBlueprintLibrary::GetRandomNameFromTagContainer(const FGameplayTagContainer& container)
{
	int tagCount = container.Num();
	if (tagCount == 0)
	{
		return NAME_None;
	}

	int comboPickIndex = FMath::RandRange(0, tagCount - 1);
	FGameplayTag pickedTag = container.GetByIndex(comboPickIndex);
	return GetTagNameLast(pickedTag);
}
