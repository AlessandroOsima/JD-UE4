

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTTService_FindNearestNPC.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTTService_FindNearestNPC : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Filter")
	bool ApplyWithEffects;

	UBTTService_FindNearestNPC(const class FObjectInitializer& PCIP);
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticServiceDescription() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
