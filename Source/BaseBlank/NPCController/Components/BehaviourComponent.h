// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BehaviourComponent.generated.h"


UENUM(BlueprintType)
enum class ENPCBehaviour : uint8
{
    Normal,
    Injured,
    Panicked,
    PowerEffect,
    Dead
};

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBehaviourComponent : public UActorComponent
{
	GENERATED_BODY()
	
private:
    ABaseCharacter * m_targetNPC;
    
public:
    UFUNCTION(BlueprintCallable, Category="JD,NPC Behaviour")
    void SetTargetNPC(ABaseCharacter * _targetNPC);
    
    UFUNCTION(BlueprintCallable, Category="JD,NPC Behaviour")
    ENPCBehaviour GetNPCBehaviour();
};
