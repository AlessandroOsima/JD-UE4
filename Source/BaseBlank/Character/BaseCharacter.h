// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Powers/BasePowerActor.h"
#include "Character/Components/DamageInfo.h"
#include "Components/PathPointsComponent.h"
#include "Components/LifeComponent.h"
#include "Components/EffectComponent.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */
struct BaseCharacterBlackBoardKeys
{
    const FName TargetActor = FName("SelfActor");
    const FName DamageInfo = FName("DamageInfo");
};

class UCharacterConfigurationAsset;

UCLASS()
class BASEBLANK_API ABaseCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()
    
public:
    UCharacterConfigurationAsset * Configuration = nullptr;
    
    UFUNCTION()
    void SetCharacterConfiguration(UCharacterConfigurationAsset * _charConfig);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="JD|Character Components")
    UBehaviorTreeComponent * BHTComponent;
    
	UPROPERTY(EditDefaultsOnly, Category = "JD|Character Components")
    UBehaviorTree * BHTAsset;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JD|Character Components")
    UBlackboardComponent * BlackboardComponent;
    
	UPROPERTY(EditDefaultsOnly, Category = "JD|Character Components")
    UBlackboardData * BlackboardAsset;
    
	UPROPERTY(VisibleAnywhere, Category = "JD|Character Components")
    UPathPointsComponent * PathPointsComponent;
    
	UPROPERTY(VisibleAnywhere, Category = "JD|Character Components")
    ULifeComponent * LifeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JD|Character Components")
	UEffectComponent * EffectComponent;

	

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void AddShieldedPower(TSubclassOf<ABasePowerActor> shieldedPower);

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	void RemoveShieldedPower(TSubclassOf<ABasePowerActor> shieldedPower);

	UFUNCTION(BlueprintCallable, Category = "JD|Powers")
	bool IsShieldedFromPower(TSubclassOf<ABasePowerActor> shieldedPower);


    
protected:
    static BaseCharacterBlackBoardKeys s_blackboardKeys;
    
    virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "JD|Powers")
	TArray<TSubclassOf<ABasePowerActor>> ShieldedFromPowers;
    
    //virtual void Tick(float _deltaTime) override;
    
public:
    
    UBlackboardComponent * GetBlackboard() const;
    BaseCharacterBlackBoardKeys GetBlackboardKeys() const;

    
    UFUNCTION(BlueprintCallable, Category="JD|Damage")
    void ApplyDamage(UDamageInfo * _damageInfo);

private:
    
    UPROPERTY()
    UDamageInfo * CurrentDamageInfo = nullptr;

    
};
