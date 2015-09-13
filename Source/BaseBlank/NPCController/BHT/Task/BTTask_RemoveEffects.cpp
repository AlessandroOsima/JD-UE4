#include "BaseBlank.h"
#include "Character/BaseCharacter.h"
#include "NPCController/NPCController.h"

#include "BTTask_RemoveEffects.h"

UBTTask_RemoveEffects::UBTTask_RemoveEffects(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	NodeName = FString("Remove Effects");
}

EBTNodeResult::Type UBTTask_RemoveEffects::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8 *NodeMemory)
{
	EBTNodeResult::Type result = EBTNodeResult::Type::Failed;

	AAIController * aiController = Cast<AAIController>(OwnerComp.GetOwner());

	if (aiController != nullptr)
	{
		APawn * target = aiController->GetPawn();

		ABaseCharacter * castedTarget = Cast<ABaseCharacter>(target);

		if (castedTarget != nullptr)
		{
			if (castedTarget->PowerInteractionsComponent->Effects.Num() > 0)
			{
				castedTarget->PowerInteractionsComponent->RemoveAllEffects();
			}
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


FString UBTTask_RemoveEffects::GetStaticDescription() const
{
	return FString::Printf(TEXT("Current Path Index"));
}

