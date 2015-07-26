// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "NPCController/NPCController.h"
#include "Character/BaseCharacter.h"
#include "BTDecorator_StateCheck.h"


UBTDecorator_StateCheck::UBTDecorator_StateCheck(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    NodeName = "Check If In State";
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

bool UBTDecorator_StateCheck::CanEnterInState(ABaseCharacter * _target, class UBehaviorTreeComponent & _ownerComp) const
{
	bool ConditionValue;
    UBehaviourComponent * cmp = GetBehaviourComponent(_ownerComp);
    
    if(cmp->GetNPCBehaviour() == BehaviourToEnter)
    {
        ConditionValue  = true;
    }
	else
	{
		ConditionValue = false;
	}

    
	return ConditionValue;
}

FString UBTDecorator_StateCheck::GetStaticDescription() const
{
    FString name = FString("Invalid");
    
    const UEnum * EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENPCBehaviour"), true);
    

    if(EnumPtr)
    {
       name = EnumPtr->GetEnumName((int8)BehaviourToEnter);
    }

	FString evalInversed = "can";
    
	if (IsInversed())
	{
		evalInversed = "cannot";
	}

    return  FString::Printf(TEXT("Check if %s enter in state %s"), *evalInversed, *name);
}

void UBTDecorator_StateCheck::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent * blk = OwnerComp.GetBlackboardComponent();

	ensure(blk);

	ABaseCharacter * target = Cast<ABaseCharacter>(blk->GetValueAsObject(TargetNPC.GetSelectedKeyID()));

	ensure(target);
	
	ANPCController * npcController = Cast<ANPCController>(target->GetController());

	ensure(npcController);

	npcController->BehaviourComponent->RegisterObserver(this, FOnBehaviorChangeDelegate::CreateUObject(this, &UBTDecorator_StateCheck::OnBehaviourChanged));
}

void UBTDecorator_StateCheck::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent * blk = OwnerComp.GetBlackboardComponent();

	ensure(blk);

	ABaseCharacter * target = Cast<ABaseCharacter>(blk->GetValueAsObject(TargetNPC.GetSelectedKeyID()));

	ensure(target);

	ANPCController * npcController = Cast<ANPCController>(target->GetController());

	ensure(npcController);

	npcController->BehaviourComponent->UnRegisterObserver(this);

}

void UBTDecorator_StateCheck::OnBehaviourChanged(ABaseCharacter * Character, ENPCBehaviour OldBehavior, ENPCBehaviour NewBehavior)
{

	ANPCController * npcController = Cast<ANPCController>(Character->GetController());

	ensure(npcController);


	bool evalResult = CanEnterInState(Character, *npcController->BHTComponent);


	if (IsInversed() == evalResult)
	{
		npcController->BHTComponent->RequestExecution(this);
	}
}
