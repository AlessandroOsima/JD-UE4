

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ApplyDamage.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTService_ApplyDamage : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ApplyDamage(const class FObjectInitializer& PCIP);


	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageToApply;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticServiceDescription() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
