// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BTDecorator_StateCheck.h"


UBTDecorator_StateCheck::UBTDecorator_StateCheck(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    NodeName = "Check If In State";
}


bool UBTDecorator_StateCheck::CanEnterInState(ABaseCharacter *_target, class UBehaviorTreeComponent & _ownerComp) const
{
    bool canEnter = false;
    UBehaviourComponent * cmp = GetBehaviourComponent(_ownerComp);
    
    if(cmp->GetNPCBehaviour() == BehaviourToEnter)
    {
        canEnter = true;
    }
    
    return canEnter;
}

FString UBTDecorator_StateCheck::GetStaticDescription() const
{
    FString name = FString("Invalid");
    
    const UEnum * EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENPCBehaviour"), true);
    

    if(EnumPtr)
    {
       name = EnumPtr->GetEnumName((int8)BehaviourToEnter);
    }
    
    return  FString::Printf(TEXT("Check if can enter in state %s"), name.GetCharArray().GetData());
}