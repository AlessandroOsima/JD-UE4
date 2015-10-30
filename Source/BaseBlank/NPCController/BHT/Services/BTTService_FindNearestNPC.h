#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Character/Effects/BaseEffect.h"
#include "BTTService_FindNearestNPC.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(NPCBHT, Log, All);

/**
 * 
 */
UCLASS()
class BASEBLANK_API UBTTService_FindNearestNPC : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector BlackboardKeyPosition;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector BlackboardKeyFoundNPCS;

	UPROPERTY(EditAnywhere, Category = "Filter")
	float SearchRadius = 0;

	UPROPERTY(EditAnywhere, Category = "Filter")
	bool ExcludeAllEffects;

	UPROPERTY(EditAnywhere, Category = "Filter")
	TArray<TSubclassOf<UBaseEffect>> ExcludeEffects;


	UBTTService_FindNearestNPC(const class FObjectInitializer& PCIP);
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticServiceDescription() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
