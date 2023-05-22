// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

FPrimaryAssetId UBaseItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(AssetType, GetFName());
}
