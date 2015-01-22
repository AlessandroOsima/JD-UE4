// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "JDBlueprintFunctionLibrary.h"
#include "Character/Components/DamageInfo.h"

UJDBlueprintFunctionLibrary::UJDBlueprintFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

UDamageInfo * UJDBlueprintFunctionLibrary::CreateDamageInfo()
{
    return NewObject<UDamageInfo>();
}


