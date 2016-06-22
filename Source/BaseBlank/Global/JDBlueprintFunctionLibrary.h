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

	//Get a power interactions component from an actor (if the actor has one)
	UFUNCTION(BlueprintCallable, Category = "JD|Powers|Powers Utilities")
	static UPowerInteractionsComponent * GetPowerInteractionsComponent(AActor * Actor);

	//Find out if an actor has a power interactions component
	UFUNCTION(BlueprintCallable, Category = "JD|Powers|Powers Utilities")
	static bool HasPowerInteractionsComponent(AActor * Actor);

	//Find all the actors with a PowerInteractionsComponent and add them to the ActorsWithPowerInteractions array
	UFUNCTION(BlueprintCallable, Category = "JD|Powers|Powers Utilities")
	static void GetActorsWithPowerInteractionComponent(TArray<AActor *> AllActors, TArray<AActor*>& ActorsWithPowerInteractions);

	//Find all the actors with a PowerInteractionsComponent and add them to the ActorsWithPowerInteractions array
	UFUNCTION(BlueprintCallable, Category = "JD|Powers|Powers Utilities")
	static bool IsPowerEffect(AActor * PowerEffect);

	//Find all the actors with a PowerInteractionsComponent and add them to the ActorsWithPowerInteractions array
	UFUNCTION(BlueprintCallable, Category = "JD|Powers|Powers Utilities")
	static bool IsPowerActor(AActor * PowerActor);
};