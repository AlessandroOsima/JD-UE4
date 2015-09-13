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

	//TODO:Lame, should become an event
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

	//TODO:Should become an event
	void RegisterObserver(UObject * Owner, FOnBehaviorChangeDelegate Observer);

	void UnRegisterObserver(UObject * Owner);

	void NotifyObservers(ENPCBehaviour OldBehavior, ENPCBehaviour NewBehavior);


	//This triggers the behavior update as (for now) 
	//it is dependent only on the life component life value and does not need to be ticked each frame
	void OnLifeValueChange(ABaseCharacter * Owner, float OldBehavior, float NewBehavior);

	virtual void OnUnregister() override;
};
