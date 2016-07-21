#include "BaseBlank.h"
#include "Character/BaseCharacter.h"
#include "NPCController/NPCController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BTService_ApplyDamage.h"

UBTService_ApplyDamage::UBTService_ApplyDamage(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	NodeName = "Apply Damage";
	bCreateNodeInstance = true;
}


FString UBTService_ApplyDamage::GetStaticServiceDescription() const
{
	return FString::Printf(TEXT("Apply %f damage to character"), DamageToApply);
}

void UBTService_ApplyDamage::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ABaseCharacter * bch = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetControlledPawn());
	ensure(bch);

	bch->LifeComponent->ApplyDamage(DamageToApply);
}
