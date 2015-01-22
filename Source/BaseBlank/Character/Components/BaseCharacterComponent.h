// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseCharacterComponent.generated.h"


class ABaseCharacter;
class UBlackboardComponent;
class UCharacterConfigurationAsset;

/**
 * 
 */
UCLASS(Blueprintable)
class BASEBLANK_API UBaseCharacterComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
    
    virtual void OnRegister() override;
    
    //Called just after the owner (if one exist) on begin play
    virtual void BeginPlay();
    
public:
    UFUNCTION()
    void SetOwnerConfiguration(UCharacterConfigurationAsset * _chrConfig);
    
    //Called by BeginPlay, notifies bps
    UFUNCTION(BlueprintImplementableEvent, Category=Lifecycle)
    void OnBeginPlay();
    
    protected:
    
    //The base character that owns this component, inizialized on registration
    ABaseCharacter * m_owner;
    
    //The base character blackboard
    UBlackboardComponent * m_ownerBlackboard;
    
   
    
protected:
    //The owner configuration
    UCharacterConfigurationAsset * m_ownerConfiguration;
    
    virtual void OnOwnerConfigurationChange();

    
};
