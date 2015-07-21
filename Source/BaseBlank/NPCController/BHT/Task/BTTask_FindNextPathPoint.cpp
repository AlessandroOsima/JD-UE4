// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BTTask_FindNextPathPoint.h"
#include "AIController.h"
#include "Character/BaseCharacter.h"
#include "Character/Components/PathPointsComponent.h"


UBTTask_FindNextPathPoint::UBTTask_FindNextPathPoint(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    BlackboardKey.AddIntFilter(this);
    NodeName = FString("Find Next Path Point");
}

EBTNodeResult::Type UBTTask_FindNextPathPoint::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8 *NodeMemory)
{
    EBTNodeResult::Type result = EBTNodeResult::Type::Failed;
    
    AAIController * aiController = Cast<AAIController>(OwnerComp.GetOwner());
    
    if(aiController != nullptr)
    {
        APawn * target = aiController->GetPawn();
        
        ABaseCharacter * castedTarget = Cast<ABaseCharacter>(target);
        
        if(castedTarget != nullptr)
        {
            UPathPointsComponent * pathPointsCmp = Cast<UPathPointsComponent>(castedTarget->GetComponentByClass(UPathPointsComponent::StaticClass()));
            
            auto PathPoints = pathPointsCmp->GetPathPoints();
            
            int currentPathIndex = GetCurrentPathIndex(OwnerComp);
            
            if(currentPathIndex < PathPoints.Num() - 1 )
            {
                currentPathIndex++;
                result = EBTNodeResult::Type::Succeeded;
            }
            else if(Loop)
            {
                currentPathIndex = 0;
                result = EBTNodeResult::Type::Succeeded;
            }
            
            OwnerComp.GetBlackboardComponent()->SetValueAsInt(BlackboardKey.GetSelectedKeyID(), currentPathIndex);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("The possessed pawn is not a BaseCharacter"))
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No ai controller found"))
    }
    
    return result;
}


void UBTTask_FindNextPathPoint::DescribeRuntimeValues(const class UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString> &Values) const
{
    Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}

FString UBTTask_FindNextPathPoint::GetStaticDescription() const
{
    return FString::Printf(TEXT("Current Path Index"));
}

int32 UBTTask_FindNextPathPoint::GetCurrentPathIndex(const class UBehaviorTreeComponent & OwnerComp) const
{
    int currentPathIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(BlackboardKey.GetSelectedKeyID());
    return currentPathIndex;
}