// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Components/DamageInfo.h"
#include "Components/PathPointsComponent.h"
#include "Components/LifeComponent.h"
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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Logic)
    UBehaviorTreeComponent * BHTComponent;
    
    UPROPERTY(EditDefaultsOnly, Category=Logic)
    UBehaviorTree * BHTAsset;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Logic)
    UBlackboardComponent * BlackboardComponent;
    
    UPROPERTY(EditDefaultsOnly, Category=Logic)
    UBlackboardData * BlackboardAsset;
    
    UPROPERTY(VisibleAnywhere, Category=Logic)
    UPathPointsComponent * PathPointsComponent;
    
    UPROPERTY(VisibleAnywhere, Category=Logic)
    ULifeComponent * LifeComponent;
    
protected:
    static BaseCharacterBlackBoardKeys s_blackboardKeys;
    
    virtual void BeginPlay() override;
    
    //virtual void Tick(float _deltaTime) override;
    
public:
    
    UBlackboardComponent * GetBlackboard() const;
    BaseCharacterBlackBoardKeys GetBlackboardKeys() const;

    
    UFUNCTION(BlueprintCallable, Category="JD,Damage")
    void ApplyDamage(UDamageInfo * _damageInfo);

private:
    
    UPROPERTY()
    UDamageInfo * CurrentDamageInfo = nullptr;

    
};
