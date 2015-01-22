// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseCharacterComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LifeComponent.generated.h"


/**
 * 
 */
UCLASS(ClassGroup=(Logic, Common), editinlinenew, meta=(BlueprintSpawnableComponent))
class BASEBLANK_API ULifeComponent : public UBaseCharacterComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Logic)
    float Life = 100;
    
    FOnBlackboardChange m_bbKeyObserver;
    
public:
    
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintCallable, Category="JD,NPC Life Management")
    float GetLife() const;
    
    UFUNCTION(BlueprintCallable, Category="JD,NPC Life Management")
    void SetLife(float _life);
    
    UFUNCTION(BlueprintCallable, Category="JD,NPC Life Management")
    void HealToFull();
    
    //Damage can be positive or negative.
    UFUNCTION(BlueprintCallable, Category="JD,NPC Life Management")
    void ApplyDamage(float _damage);
    
    //Listener on the blk for damage data
    void OnApplyDamage(const class UBlackboardComponent * _blk, FBlackboard::FKey _key);
	
    float GetMaxLife() const;
    
protected:
    virtual void OnOwnerConfigurationChange() override;
    
};
