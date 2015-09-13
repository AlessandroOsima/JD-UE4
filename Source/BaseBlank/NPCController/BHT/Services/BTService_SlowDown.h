

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SlowDown.generated.h"

/**
 * Reduce actor max speed by a value every frame
 */
UCLASS()
class BASEBLANK_API UBTService_SlowDown : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Node")
	float SpeedToDecrement;

public:
	UBTService_SlowDown(const class FObjectInitializer& PCIP);
	virtual FString GetStaticServiceDescription() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
