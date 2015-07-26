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

DECLARE_DELEGATE_ThreeParams(FOnBehaviorChangeDelegate, ABaseCharacter * , ENPCBehaviour , ENPCBehaviour);

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBehaviourComponent : public UActorComponent
{
	GENERATED_BODY()
	
private:
    ABaseCharacter * m_targetNPC;

	TMap<UObject *, FOnBehaviorChangeDelegate> Observers;

	ENPCBehaviour CurrentBehavior = ENPCBehaviour::Normal;
    
	void ComputeNPCBehaviour(bool DoNotifyObservers = true);
public:
	UBehaviourComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

    UFUNCTION(BlueprintCallable, Category="JD,NPC Behaviour")
    void SetTargetNPC(ABaseCharacter * _targetNPC);
    
    UFUNCTION(BlueprintCallable, Category="JD,NPC Behaviour")
	ENPCBehaviour GetNPCBehaviour();

	void RegisterObserver(UObject * Owner, FOnBehaviorChangeDelegate Observer);

	void UnRegisterObserver(UObject * Owner);

	void NotifyObservers(ENPCBehaviour OldBehavior, ENPCBehaviour NewBehavior);
};
