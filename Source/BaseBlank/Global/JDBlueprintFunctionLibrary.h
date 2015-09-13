// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "JDBlueprintFunctionLibrary.generated.h"

class UDamageInfo;
/**
 * 
 */
UCLASS()
class BASEBLANK_API UJDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	//Global Utilities
	// JD/Global Functions

	//Create a damage info  TODO:This should probably be a wrapper around CreateObject
    UFUNCTION(BlueprintCallable, Category="JD|Global Functions")
    static UDamageInfo * CreateDamageInfo();

	//Instantiate an object from blueprint at runtime
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = "JD|Global Functions")
	static UObject * CreateObject(TSubclassOf<UObject> UC, AActor * Creator);

	//Utilities related to power use
	// JD/Powers

	//Push a new bht on an NPCController controlled BaseCharacter
	UFUNCTION(BlueprintCallable, Category = "JD|Powers|Powers Utilities")
	static bool PushBHTOnNPC(AActor * NPC, UBehaviorTree * BHTAssetToLoad);

	//Pop a bht from an NPCController controlled BaseCharacter
	UFUNCTION(BlueprintCallable, Category = "JD|Powers|Powers Utilities")
	static bool PopBHTOnNPC(AActor * NPC);
};