

#pragma once

#include "GameplayDebuggingComponent.h"
#include "Global/BaseBlankGameMode.h"
#include "Camera/CameraPawn.h"
#include "JDDebuggingComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UJDDebuggingComponent : public UGameplayDebuggingComponent
{
	GENERATED_BODY()
	
	
protected:
	virtual void CollectDataToReplicate(bool bCollectExtendedData) override;
	
public:

	UPROPERTY(Replicated)
	ABaseBlankGameMode * JDGameMode;


};
