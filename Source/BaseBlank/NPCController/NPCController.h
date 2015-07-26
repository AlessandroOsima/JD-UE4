// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCController/Components/BehaviourComponent.h"
#include "NPCController.generated.h"

/**
 * 
 */

struct NPCControllerBlackBoardKeys
{
    const FName TargetObject = FName("PossessedPawn"); //The Object the AI is currently moving to
    const FName TargetLocation = FName("PossessedPawn"); //The position the AI is currently moving to (the position of TargetObject)
    const FName TargetActor = FName("PossessedPawn"); //The (you guessed it) currently possesed pawn
    const FName TargetIndex = FName("TargetIndex"); //The index of the next point to reach in the path points array
};

UCLASS()
class BASEBLANK_API ANPCController : public AAIController
{
    GENERATED_UCLASS_BODY()
    
public:
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JD|Controller Logic")
    UBehaviorTreeComponent * BHTComponent;
    
	UPROPERTY(EditDefaultsOnly, Category = "JD|Controller Logic")
    UBehaviorTree * BHTAsset;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JD|Controller Logic")
    UBlackboardComponent * BlackboardComponent;
    
    
	UPROPERTY(EditDefaultsOnly, Category = "JD|Controller Logic")
    UBlackboardData * BlackboardAsset;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "JD|Controller Logic")
    UBehaviourComponent * BehaviourComponent;
    
    static NPCControllerBlackBoardKeys BlackboardKeys;
    
    virtual void BeginPlay() override;
    virtual void Tick(float _deltaTime) override;
    virtual void Possess(APawn* _pawn) override;
    void SetupBlackboardKeys();
    
public:
    
    NPCControllerBlackBoardKeys GetBlackboardKeys() const
    {
        return ANPCController::BlackboardKeys;
    }
    
	UFUNCTION(BlueprintCallable, Category = "JD|Controller Logic")
	void PushNewBHTAsset(UBehaviorTree * BHTAssetToLoad);

	UFUNCTION(BlueprintCallable, Category = "JD|Controller Logic")
	void PopBHTAsset();

};
