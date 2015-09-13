// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseCharacterComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LifeComponent.generated.h"


/**
 * 
 */

//The actor being affected by the life change, the old life value, the new life value

UCLASS(ClassGroup=(Logic, Common), editinlinenew, meta=(BlueprintSpawnableComponent))
class BASEBLANK_API ULifeComponent : public UBaseCharacterComponent
{
public:
	//No ensurance to the actual life value in the LifeComponent 
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FLifeChangeEvent, ABaseCharacter *, float, float);

private:

	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Logic)
    float Life = 100;

	FLifeChangeEvent LifeChange;

public:
    
	FLifeChangeEvent & OnLifeChange() 
	{ 
		return LifeChange; 
	}

    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintCallable, Category="JD|NPC Life Management")
    float GetLife() const;
    
    UFUNCTION(BlueprintCallable, Category="JD|NPC Life Management")
    void SetLife(float _life);
    
    UFUNCTION(BlueprintCallable, Category="JD|NPC Life Management")
    void HealToFull();
    
    //Damage can be positive or negative.
    UFUNCTION(BlueprintCallable, Category="JD|NPC Life Management")
    void ApplyDamage(float _damage);
    
    //Listener on the blk for damage data
	EBlackboardNotificationResult OnApplyDamage(const class UBlackboardComponent & _blk, FBlackboard::FKey _key);
	
	UFUNCTION(BlueprintCallable, Category = "JD|NPC Life Management")
    float GetMaxLife() const;

	//You are terminated
	UFUNCTION(BlueprintCallable, Category = "JD|NPC Life Management")
	void Kill();

protected:
    virtual void OnOwnerConfigurationChange() override;
    
};
