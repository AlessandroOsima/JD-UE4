#include "BaseBlank.h"
#include "BTService_SlowDown.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


UBTService_SlowDown::UBTService_SlowDown(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	NodeName = "Slow Down";
	BlackboardKey.AddObjectFilter(this, ACharacter::StaticClass());
}

FString UBTService_SlowDown::GetStaticServiceDescription() const
{
	return TEXT("Reduce actor speed every tick");
}

void UBTService_SlowDown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACharacter * target = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()));
	target->GetCharacterMovement()->MaxWalkSpeed -= SpeedToDecrement;
}
