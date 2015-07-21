// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BTDecorator_BaseStateCheck.h"
#include "Character/BaseCharacter.h"
#include "NPCController/Components/BehaviourComponent.h"
#include "NPCController/NPCController.h"

UBTDecorator_BaseStateCheck::UBTDecorator_BaseStateCheck(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
    NodeName = "Base";
    TargetNPC.AddObjectFilter(this, ABaseCharacter::StaticClass());
}

void UBTDecorator_BaseStateCheck::InitializeFromAsset(class UBehaviorTree & _asset)
{
    Super::InitializeFromAsset(_asset);
    
    UBlackboardData* BBAsset = GetBlackboardAsset();
    TargetNPC.CacheSelectedKey(BBAsset);
}

FString UBTDecorator_BaseStateCheck::GetStaticDescription() const
{
    return FString::Printf(TEXT("State %s"), NodeName.GetCharArray().GetData());
}

bool UBTDecorator_BaseStateCheck::CalculateRawConditionValue(class UBehaviorTreeComponent &_ownerComp, uint8 *_nodeMemory) const
{
    UBlackboardComponent * blk = _ownerComp.GetBlackboardComponent();
    
    check(blk);
    
    ABaseCharacter * target = Cast<ABaseCharacter>(blk->GetValueAsObject(TargetNPC.GetSelectedKeyID()));
    
    check(target);
    
    //Check for state conditions
    return CanEnterInState(target, _ownerComp);
}

UBehaviourComponent * UBTDecorator_BaseStateCheck::GetBehaviourComponent(class UBehaviorTreeComponent & _ownerComp) const
{
   ANPCController * npcCtr = Cast<ANPCController>(_ownerComp.GetOwner());
   
    if(npcCtr != nullptr)
    {
        return npcCtr->BehaviourComponent;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[UBTDecorator_BaseStateCheck]Unable to find NPCController"))
        check(npcCtr)
    }
    
    return nullptr;
}

bool UBTDecorator_BaseStateCheck::CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent & _ownerComp) const
{
    return false;
}

#if WITH_EDITOR
FName UBTDecorator_BaseStateCheck::GetNodeIconName() const
{
    return FName("BTEditor.Graph.BTNode.Decorator.CompareBlackboardEntries.Icon");
}
#endif	// WITH_EDITOR