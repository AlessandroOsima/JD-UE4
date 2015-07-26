// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "JDBlueprintFunctionLibrary.generated.h"


class UDamageInfo;
/**
 * 
 */
UCLASS()
class BASEBLANK_API UJDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

    UFUNCTION(BlueprintCallable, Category="JD|Global Functions")
    static UDamageInfo * CreateDamageInfo();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = "JD|Global Functions")
	static UObject * CreateObject(TSubclassOf<UObject> UC, AActor * Creator);
	
};
