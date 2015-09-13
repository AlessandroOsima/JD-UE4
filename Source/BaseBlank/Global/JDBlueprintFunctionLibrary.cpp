// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "JDBlueprintFunctionLibrary.h"
#include "Character/BaseCharacter.h"
#include "NPCController/NPCController.h"
#include "Character/Components/DamageInfo.h"

UJDBlueprintFunctionLibrary::UJDBlueprintFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

UDamageInfo * UJDBlueprintFunctionLibrary::CreateDamageInfo()
{
    return NewObject<UDamageInfo>();
}

UObject * UJDBlueprintFunctionLibrary::CreateObject(TSubclassOf<UObject> UC, AActor * Creator)
{

	UObject * created = NewObject<UObject>((UObject*)Creator, UC);
	return  created;
}

bool  UJDBlueprintFunctionLibrary::PushBHTOnNPC(AActor * NPC, UBehaviorTree * BHTAssetToLoad)
{
	ensure(NPC);
	ensure(BHTAssetToLoad);

	ABaseCharacter * character = Cast<ABaseCharacter>(NPC);

	if (!character)
	{
		return false;
	}

	ANPCController * controller = Cast<ANPCController>(character->GetController());

	if (!controller)
	{
		return false;
	}

	controller->PushNewBHTAsset(BHTAssetToLoad);

	return true;
}

bool UJDBlueprintFunctionLibrary::PopBHTOnNPC(AActor * NPC)
{

	ensure(NPC);

	ABaseCharacter * character = Cast<ABaseCharacter>(NPC);

	if (!character)
	{
		return false;
	}

	ANPCController * controller = Cast<ANPCController>(character->GetController());

	if (!controller)
	{
		return false;
	}

	controller->PopBHTAsset();

	return true;
}

