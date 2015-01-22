// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
#include "DamageInfo.generated.h"

UCLASS()
class UDamageInfo : public UObject
{
    GENERATED_UCLASS_BODY()
    
    public :
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JD,Damage Data")
    float DamageAmount = 0.f;
    
    
};
